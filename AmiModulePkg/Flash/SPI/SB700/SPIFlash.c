//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file SPIFlash.c
    Flash update routines

**/

//============================================================================
// Includes
//============================================================================
#include <Uefi.h>
#include <Token.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/IoLib.h>
#include <FlashPart.h>
#include <../SpiFlash.h>
#include "SpiFlashInc.h"
//============================================================================
// Local defines for transaction types
//============================================================================
// ITE8512 SPI register defines.
#if defined(REG80_FIFO_SUPPORT) && (REG80_FIFO_SUPPORT == 1)
#define SPI_MAX_DATA_TRANSFER   64
#define FIFO_ADDRESS_0          0x80
#define FIFO_ADDRESS_1          0x81
#define FIFO_ADDRESS_2          0x82
#define FIFO_ADDRESS_3          0x83
#define FIFO_ADDRESS_4          0x84
#else
#define SPI_MAX_DATA_TRANSFER   4
#define FIFO_ADDRESS_0          0x0C
#define FIFO_ADDRESS_1          0x0C
#define FIFO_ADDRESS_2          0x0C
#define FIFO_ADDRESS_3          0x0C
#define FIFO_ADDRESS_4          0x0C
#endif
#define SPI_PREFIX_WRITE_S_EN   0x1
#define SPI_PREFIX_WRITE_EN     0x0

#define THREE_BYTE_ADDR_MODE                ((UINT8)0x3)
#define FOUR_BYTE_ADDR_MODE                 ((UINT8)0x4)
#define SPI_COMMAND_EN4B                    ((UINT8)0xB7)
#define SPI_COMMAND_EX4B                    ((UINT8)0xE9)
#define SPI_COMMAND_ISSI_EX4B               ((UINT8)0x29)
#define SPI_COMMAND_GD_READ_STATUS_2        ((UINT8)0x35)
#define SPI_COMMAND_ISSI_READ_BANK_ADDRESS  ((UINT8)0x16)
#define SPI_COMMAND_MICRON_READ_FLAG_STATUS ((UINT8)0x70)
#define SPI_COMMAND_MXIC_READ_CONFIG        ((UINT8)0x15)
#define SPI_COMMAND_WINBOND_READ_STATUS_3   ((UINT8)0x15)

#define F17_30H_RAW_ID          0x00830F00ul
#define F17_60H_RAW_ID          0x00860F00ul
#define F17_70H_RAW_ID          0x00870F00ul
#define F17_RAW_FAMILY_ID_MASK  0x0FFF0F00ul
#define F19_20H_RAW_ID          0x00A20F00ul

#define SPI_READ_USING_4_BTYE_ADDR_COMMAND      ((UINT8)0x13)
#define SPI_PROGRAM_USING_4_BTYE_ADDR_COMMAND   ((UINT8)0x12)
#define SPI_ERASE_USING_4_BTYE_ADDR_COMMAND     ((UINT8)0x21)
#define SPI_ERASE_64K_USING_4_BTYE_ADDR_COMMAND ((UINT8)0xDC)

typedef enum  {
    SPI_READ,
    SPI_PROGRAM,
    SPI_ERASE,
    SPI_MAX
} SPI_COMMAND_TYPE;

//============================================================================
// Module level global data
//============================================================================
extern UINT16       gFlashId;
extern FLASH_PART   *gFlashApi;
extern UINTN        gAmiFlashDeviceBase;
extern UINT32       gFlashBlockSize;
//============================================================================
// Local prototypes
//============================================================================
static BOOLEAN
EFIAPI
CommonSpiEraseCommand(
    IN  volatile UINT8  *BlockAddress
);

static EFI_STATUS
EFIAPI
CommonSpiEraseCommandEx(
    IN  volatile UINT8  *BlockAddress,
    IN  UINT32          Length,
    IN  BOOLEAN         IsMappedAddress
);

static BOOLEAN
EFIAPI
CommonSpiProgramCommand(
    IN      volatile UINT8  *Address,
    IN      UINT8           *Byte,
    IN  OUT UINT32          *Length,
    IN      BOOLEAN         IsMappedAddress
);

static VOID
EFIAPI
CommonSpiReadCommand(
    IN      volatile UINT8  *Address,
    OUT     UINT8           *Byte,
    IN  OUT UINT32          *Length,
    IN      BOOLEAN         IsMappedAddress
);

static VOID
EFIAPI
CommonSpiBlockWriteEnable(
    IN  volatile UINT8  *BlockAddress,
    IN  UINT32          Length,
    IN  BOOLEAN         IsMappedAddress
);

static VOID
EFIAPI
CommonSpiBlockWriteDisable(
    IN  volatile UINT8  *BlockAddress,
    IN  UINT32          Length,
    IN  BOOLEAN         IsMappedAddress
);

static VOID
EFIAPI
CommonSpiDeviceWriteEnable(
    VOID
);

static VOID
EFIAPI
CommonSpiDeviceWriteDisable(
    VOID
);

static BOOLEAN
EFIAPI
CommonSpiGetEraseGranularity(
    IN  OUT UINT32  **Granularity,
    IN  OUT UINT32  *NumberOfEntries
);

static VOID
EFIAPI
CommonSpiDeviceVirtualFixup(
    IN  EFI_RUNTIME_SERVICES    *Rs
);

VOID
SpiBlockProtectUpdate(
    IN  UINT32  FlashOffset,
    IN  UINT32  Length,
    IN  UINT8   StatusData
);

UINT8
EFIAPI
JedecCheckAddressMode(
    IN  UINT32  FlashId
);

BOOLEAN
EFIAPI
JedecEnterAddressMode(
    IN  UINT32  FlashId,
    IN  UINT8   Mode
);

BOOLEAN
EFIAPI
Is4ByteAddressMode();

UINT8
EFIAPI
GetSpiFlashAddressMode(
    IN  UINT32  FlashId
);

BOOLEAN
Get4ByteAddressReadCommand(
    IN  OUT UINT8   *ReadCmd
);

BOOLEAN
Get4ByteAddressProgramCommand(
    IN  OUT UINT8   *ProgramCmd
);

BOOLEAN
Get4ByteAddressEraseCommand(
    IN  OUT UINT8   *EraseCmd
);

BOOLEAN
ConvertTo4ByteAddressCommandSet(
    IN      UINT32              SpiStartAddress,
    IN      UINT32              Size,
    IN      SPI_COMMAND_TYPE    CmdType,
    IN  OUT UINT8               *Cmd
);

VOID
CommonSpiReadBytes(
    IN      volatile UINT8  *ByteAddress,
    OUT     UINT8           *Byte,
    IN  OUT UINT32          *Length
);

BOOLEAN
EFIAPI
SwitchSpiFlashAddressMode(
    IN  UINT32  FlashId,
    IN  UINT8   Mode
);

UINT8
EFIAPI
InternalCheckSpiFlashAddressMode();

typedef 
BOOLEAN 
(EFIAPI *ADDRESS_MODE_ENTRY) (
    IN UINT32  FlashId,
    IN UINT8   Mode
);

typedef 
UINT8 
(EFIAPI *ADDRESS_MODE_CHECK_ENTRY) (
    IN UINT32  FlashId
);

//============================================================================
// Local Variables
//============================================================================
FLASH_PART gCommonSpiFlash = {
    CommonSpiReadCommand,
    CommonSpiEraseCommand,
    CommonSpiEraseCommandEx,
    CommonSpiProgramCommand,
    CommonSpiBlockWriteEnable,
    CommonSpiBlockWriteDisable,
    CommonSpiDeviceWriteEnable,
    CommonSpiDeviceWriteDisable,
    CommonSpiGetEraseGranularity,
    CommonSpiDeviceVirtualFixup,
    1,                      // default value, should be changed in Init function
    SECTOR_SIZE_4KB,        // default value, should be changed in Init function
    NULL                    // Flash Part Number Pointer
};
EX_FLASH_PART gExFlashPart = {
      {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},0,0},
      FLASH_SIZE,         // flash size, should be changed in Init function
      0,                  // flash part id, should be changed in Init function
      0                   // flash part string, should be changed in Init function
};

volatile UINT8  *gSpiBase = (UINT8*)(UINTN)SPI_BASE_ADDRESS;
UINT32          gBiosRegionBase = 0;
UINT8           gDeviceVirtual = 0;
UINT8           gDeviceWriteEnabled = 0;
BOOLEAN         gIsSpiMmioAddressMappedBottom16M = TRUE;
static UINT32   gGranularity[4];

//============================================================================
// Function Definitions
/**
    The function delays for flash operation.

**/
VOID
IoDelay(
    VOID
)
{
    UINT8   Timeout;

    for ( Timeout = 0; Timeout < 33; Timeout++ )
    {
        IoWrite8( 0xEB, 0x55 );
        IoWrite8( 0xEB, 0xAA );
    }

    return ;
}

/**
    This function gets the Base and Limit from the specified Flash Region

    @param Type Type of Flash region.   
    @param Base Base Address of region. 
    @param Limit Limit Address of region.

    @retval EFI_SUCCESS Operation Completed
    @retval EFI_UNSUPPORTED Operation not Completed
**/
EFI_STATUS
GetFlashRegion(
    FLASH_REGION_TYPE   Type,
    UINTN               *Base,
    UINTN               *Limit
)
{
    if( Type != FlashRegionBios ) return EFI_UNSUPPORTED;
    if( Base != NULL ) *Base = 0;
    if( Limit != NULL ) *Limit = FLASH_SIZE - 1;
    return EFI_SUCCESS;
}

/**
    This function gets the Maximum Limit from the specified Flash Region

    @param Limit Maximum Limit Address of region.

    @retval EFI_SUCCESS Operation Completed
**/
EFI_STATUS 
GetMaxRegionLimit(
    UINTN   *Limit
)
{
    UINTN   Index;
    UINTN   MaxRegionLimit;

    for( *Limit = MaxRegionLimit = Index = 0; Index < FlashRegionMax; Index++ )
    {
        if( EFI_ERROR(GetFlashRegion( Index, NULL, &MaxRegionLimit )) ) continue;
        if( MaxRegionLimit > *Limit ) *Limit = MaxRegionLimit;
    }
    return EFI_SUCCESS;
}

/**
    This function set Tx and Rx byte count

    @param ByteCount Top byte is Rx, low byte is Tx
**/
VOID
SpiTxRxByteCount(
    UINT16  ByteCount
)
{
#if defined(YANGTZE_SPI) && (YANGTZE_SPI == 1)
    // SpiExtRegIndx [5] - TxByteCount
    *(volatile UINT8*)(gSpiBase + 0x1E) = 5;
    *(volatile UINT8*)(gSpiBase + 0x1F) = ByteCount & 0xFF;
    // SpiExtRegData [6] - RxByteCount
    *(volatile UINT8*)(gSpiBase + 0x1E) = 6;
    *(volatile UINT8*)(gSpiBase + 0x1F) = ByteCount >> 8;;
#else
    // SPI Ctrl - BIT[11..8] : TxByteCount, BIT[15..12] - RxByteCount
    *(volatile UINT8*)(gSpiBase + 1) = ByteCount;
#endif
}

/**
    This routine resets Internal FIFO port.
**/
VOID
ResetInternalFIFOPointer(
    VOID
)
{
    do
    {
        *(volatile UINT8*)(gSpiBase + 2) |= 0x10;
    }while( *(volatile UINT8*)(gSpiBase + 0x0D) & 0x7 );
}

/**
    This routine execute SPI OpCode.
**/
VOID
ExecuteSpiCommand(
    VOID
)
{
    *(volatile UINT8*)(gSpiBase + 2) |= 1;
}

/**
    This routine wait SPI cycle to be done.
**/
VOID
WaitForSpiCycleDone(
    VOID
)
{
    UINT8   Status;
    UINT16  Timeout;

    for( Timeout = 0; Timeout < 0xFFFF; Timeout++ )
    {
        Status = *(volatile UINT8*)(gSpiBase + 2);
        if( !( Status & BIT0 ) )
            break;
    }
}

/**
    This routine send write enable command.
**/
VOID
SpiWriteEnable(
    VOID
)
{
    UINT8   Command;

    Command = gExFlashPart.FlashCommandMenu.WriteEnable.Opcode;
    *(volatile UINT8*)gSpiBase = Command;
    // TxByte = 0, RxByte = 0
    SpiTxRxByteCount( 0 );
    ExecuteSpiCommand();
    WaitForSpiCycleDone();
    return;
}

/**
    This function returns the 4 BYTE address READ command opcode based on 
    Manufacture ID and Device ID.

    @param ReadCmd which READ command should be used

    @retval TRUE, ReadCmd is valid
    @retval FALSE, invalid paramenter or 4 BYTE address read command is not supported
**/
BOOLEAN
Get4ByteAddressReadCommand(
    IN  OUT UINT8   *ReadCmd
)
{
    if( ReadCmd == NULL )
    {
        return FALSE;
    }

    switch( (UINT16)(gExFlashPart.FlashVenDevId) )
    {
        default:
            *ReadCmd = SPI_READ_USING_4_BTYE_ADDR_COMMAND;   // 4NORD, READ4B, 4-BYTE READ
    }
    return TRUE;
}

/**
    This function returns the 4 BYTE address PROGRAM command opcode based on 
    Manufacture ID and Device ID.

    @param ProgramCmd which PROGRAM command should be used

    @retval TRUE, ProgramCmd is valid
    @retval FALSE, invalid paramenter or 4 BYTE address program command is not supported
**/
BOOLEAN
Get4ByteAddressProgramCommand(
    IN  OUT UINT8   *ProgramCmd
)
{
    if( ProgramCmd == NULL )
    {
        return FALSE;
    }

    switch( (UINT16)(gExFlashPart.FlashVenDevId ))
    {
        default:
            *ProgramCmd = SPI_PROGRAM_USING_4_BTYE_ADDR_COMMAND;    // 4PP, PP4B, 4-BYTE PAGE PROGRAM
    }
    return TRUE;
}

/**
    This function returns the 4 BYTE address ERASE command opcode based on 
    Manufacture ID and Device ID.

    @param EraseCmd which ERASE command should be used

    @retval TRUE, EraseCmd is valid
    @retval FALSE, invalid paramenter or 4 BYTE address erase command is not supported
**/
BOOLEAN
Get4ByteAddressEraseCommand(
    IN  OUT UINT8   *EraseCmd
)
{
    if( EraseCmd == NULL )
    {
        return FALSE;
    }

    switch( (UINT16)(gExFlashPart.FlashVenDevId) )
    {
        default:
            *EraseCmd = SPI_ERASE_USING_4_BTYE_ADDR_COMMAND;    // 4SER, SE4B, 4-BYTE 4KB SUBSECTOR ERASE
    }
    return TRUE;
}

/**
    This function returns the 4 BYTE address ERASE command opcode based on
    Manufacture ID and Device ID.

    @param Erase64KCmd which ERASE command should be used

    @retval TRUE, Erase64KCmd is valid
    @retval FALSE, invalid paramenter or 4 BYTE address erase command is not supported
**/
BOOLEAN
Get4ByteAddressErase64KCommand(
    IN  OUT UINT8   *Erase64KCmd
)
{
    if( Erase64KCmd == NULL )
        return  FALSE;

    switch( (UINT16)(gExFlashPart.FlashVenDevId) )
    {
        default:
            *Erase64KCmd = SPI_ERASE_64K_USING_4_BTYE_ADDR_COMMAND;
    }

    return TRUE;
}

/**
    This function determine which command should return, 4 BYTE address command or 3 BYTE addresss command.

    @param SpiStartAddress address to be read from
    @param Size size of data is going to be read
    @param CmdType 
    @param ReadCmd which command should be used

    @retval TRUE, Cmd Updated
    @retval FALSE, Cmd is not the 4 byte address command
**/
BOOLEAN
ConvertTo4ByteAddressCommandSet(
    IN      UINT32              SpiStartAddress,
    IN      UINT32              Size,
    IN      SPI_COMMAND_TYPE    CmdType,
    IN  OUT UINT8               *Cmd
)
{
    UINT32  SpiEndAddress = SpiStartAddress + (Size - 1);
    if( (Cmd == NULL) || (CmdType >= SPI_MAX) )
    {
        return FALSE;
    }
    // overflow check
    if( SpiEndAddress < SpiStartAddress )
    {
        return FALSE;
    }

    if( ((SpiEndAddress & BIT31) != 0) ||
        (((SpiEndAddress & BIT31) == 0) && (SpiEndAddress < (UINT32)SIZE_16MB)) )
    {
        // If MMIO address or SPI address is less than 16MB, this function will do nothing and directly return.
        return FALSE;
    }
    else
    {
        // If Flash part size is less than 16MB, 4 BYTE address related command is not supported.
        if( gExFlashPart.FlashCapacity <= (UINT32)SIZE_16MB )
        {
            return FALSE;
        }
        switch( CmdType )
        {
            case SPI_READ:
                if( !Get4ByteAddressReadCommand( Cmd ) )
                {
                    return FALSE;
                }
                break;
            case SPI_PROGRAM:
                if( !Get4ByteAddressProgramCommand( Cmd ) )
                {
                    return FALSE;
                }
                break;
            case SPI_ERASE:
                if( (Size == SECTOR_SIZE_64KB) && (Get4ByteAddressErase64KCommand( Cmd ) == TRUE) )
                    return TRUE;
                if( !Get4ByteAddressEraseCommand( Cmd ))
                {
                    return FALSE;
                }
                break;
            default:
                break;
        }
        return TRUE;
    }
}

/**
    This funciton returns SPI flash part address mode.

    @param FlashId Flash Manufacture ID, Device ID and Capacity.

    @retval returns Flash device is in THREE_BYTE_ADDR_MODE or FOUR_BYTE_ADDR_MODE
**/
UINT8
EFIAPI
JedecCheckAddressMode(
    IN  UINT32  FlashId
)
{
    UINT8   Command;
    UINT8   ModeBit;

    switch( (UINT8)FlashId )
    {
        case 0xEF: //Winbond
            Command = SPI_COMMAND_WINBOND_READ_STATUS_3;
            ModeBit = (UINT8)BIT0;
            break;
        case 0x9D: //ISSI
            Command = SPI_COMMAND_ISSI_READ_BANK_ADDRESS;
            ModeBit = (UINT8)BIT7;
            break;
        case 0xC2: //MXIC
            Command = SPI_COMMAND_MXIC_READ_CONFIG;
            ModeBit = (UINT8)BIT5;
            break;
        case 0xC8: //GigaDevice
            if( ((UINT16)FlashId == GD_25Qxx_ID) )
            {
                //GD25R256D
                Command = SPI_COMMAND_GD_READ_STATUS_2;
                ModeBit = (UINT8)BIT0;
            }
            else
            {
                Command = SPI_COMMAND_MICRON_READ_FLAG_STATUS;
                ModeBit = (UINT8)BIT0;
            }
            break;
        case 0x20:
            if( ((UINT16)FlashId == XMC_25RHxxC_ID) )
            {
                //XM25RH256
                Command = SPI_COMMAND_WINBOND_READ_STATUS_3;
                ModeBit = (UINT8)BIT0;
            }
            else if( ((UINT16)FlashId == XMC_25QHxx_ID) ||
                     ((UINT16)FlashId == STM_25PFxx_ID) )
            {
                //XM25QH256 or XM25QU256
                Command = SPI_COMMAND_ISSI_READ_BANK_ADDRESS;
                ModeBit = (UINT8)BIT7;
            }
            else
            {
                //MT25Q256
                Command = SPI_COMMAND_MICRON_READ_FLAG_STATUS;
                ModeBit = (UINT8)BIT0;
            }
            break;
        default:
            return THREE_BYTE_ADDR_MODE;
    }

    // prepare to send command
    ResetInternalFIFOPointer();
    *(volatile UINT8*)gSpiBase = Command;

    // TxByte = 0, RxByte = 0
    SpiTxRxByteCount( 0x01 << 8 );
    ExecuteSpiCommand();
    WaitForSpiCycleDone();
    ResetInternalFIFOPointer();
    Command = *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_0);

    return ( Command & ((UINT8)ModeBit) ) ? FOUR_BYTE_ADDR_MODE : THREE_BYTE_ADDR_MODE;
}

/**
    This function changes SPI flash part address mode.

    @param FlashId Flash Manufacture ID, Device ID and Capacity.
    @param Mode THREE_BYTE_ADDR_MODE or FOUR_BYTE_ADDR_MODE

    @retval TRUE Successfully change mode
    @retval FALSE Failed to change mode
**/
BOOLEAN
EFIAPI
JedecEnterAddressMode(
    IN  UINT32  FlashId,
    IN  UINT8   Mode
)
{
    UINT8   Command;

    if( Mode == THREE_BYTE_ADDR_MODE )
    {
        if( ((UINT8)FlashId == 0x9D) ||
            ((UINT16)FlashId == XMC_25QHxx_ID) ||
            ((UINT16)FlashId == STM_25PFxx_ID) )
        {
            //ISSI device or XMC XM25Q device
            Command = SPI_COMMAND_ISSI_EX4B;
        }
        else
        {
            Command = SPI_COMMAND_EX4B;
        }
    }
    else if( Mode == FOUR_BYTE_ADDR_MODE )
    {
        Command = SPI_COMMAND_EN4B;
    }
    else
    {
        return FALSE;
    }

    // prepare to send command
    ResetInternalFIFOPointer();
    *(volatile UINT8*)gSpiBase = Command;

    // TxByte = 0, RxByte = 0
    SpiTxRxByteCount( 0 );
    ExecuteSpiCommand();
    WaitForSpiCycleDone();

    return TRUE;
}

/**
    This function configures SPI flash addressing mode to 3 or 4 bytes address mode.

    @param FlashId Flash Manufacture ID, Device ID and Capacity.
    @param Mode THREE_BYTE_ADDR_MODE or FOUR_BYTE_ADDR_MODE

    @retval TRUE Successfully change mode
    @retval FALSE Failed to change mode or changing addressing mode is not supproted by device
**/
BOOLEAN
EFIAPI
SwitchSpiFlashAddressMode(
    IN  UINT32  FlashId,
    IN  UINT8   Mode
)
{
    // Do nothing if the flash is less than or equal to 16MB
    if( gExFlashPart.FlashCapacity <= SIZE_16MB )
    {
        return FALSE;
    }

    return JedecEnterAddressMode( FlashId, Mode );
}

/**
    This function configures SPI flash addressing mode to 3 or 4 bytes address mode.

    @param FlashId Flash Manufacture ID, Device ID and Capacity.

    @retval returns Flash device is in THREE_BYTE_ADDR_MODE or FOUR_BYTE_ADDR_MODE 
**/
UINT8
EFIAPI
GetSpiFlashAddressMode(
    IN  UINT32  FlashId
)
{
    // Return THREE_BYTE_ADDR_MODE if the flash is less than or equal to 16MB
    if( gExFlashPart.FlashCapacity <= SIZE_16MB )
    {
        return  THREE_BYTE_ADDR_MODE;
    }

    return JedecCheckAddressMode( FlashId );
}

/**
    This internal function configures SPI flash addressing mode to 3 or 4 bytes address mode.

    @param FlashId Flash Manufacture ID, Device ID and Capacity.

    @retval returns Flash device is in THREE_BYTE_ADDR_MODE or FOUR_BYTE_ADDR_MODE 
**/
UINT8
EFIAPI
InternalCheckSpiFlashAddressMode()
{
    if( gExFlashPart.FlashVenDevId != 0 )
    {
        return GetSpiFlashAddressMode( gExFlashPart.FlashVenDevId );
    }
    return THREE_BYTE_ADDR_MODE;
}

/**
    Check if the changing to 4 byte address mode is neended for current platform.

    @retval TRUE Now is in 4 byte address mode
    @retval FALSE Now is in 3 byte address mode
**/
BOOLEAN
EFIAPI
IsPlatformLanuchedOn4ByteAddress()
{
    UINT32  Eax;
    UINT32  Ebx;
    UINT32  Ecx;
    UINT32  Edx;

    // If CPU >=  family 17 model 30h && SPIx50[0] == 1)
    // flash mode = 4 byte;
    AsmCpuid(
        0x00000001,
        &Eax,
        &Ebx,
        &Ecx,
        &Edx );
    Eax &= F17_RAW_FAMILY_ID_MASK;
    if( (Eax == F17_30H_RAW_ID) ||
        (Eax == F17_60H_RAW_ID) ||
        (Eax == F17_70H_RAW_ID) ||
        (Eax == F19_20H_RAW_ID) )
    {
        // This is Family 17h model 30-3Fh | 70-7Fh
        // Check SPIx50[0] == 1
        if( *(volatile UINT8*)(gSpiBase + 0x50) & BIT0 )
            // If SPIROM_Page[0] == 1, 0xFFxx_xxxx maps to top 16MB
            if( *(volatile UINT8*)(gSpiBase + 0x5C) & BIT0 )
            {
                gIsSpiMmioAddressMappedBottom16M = FALSE;
            }
            return TRUE;
    }

    return  FALSE;
}

/**
    This function checks the current SPI address mode is 3 byte or 4 byte mode.

    @retval TRUE Now is in 4 byte address mode
    @retval FALSE Now is in 3 byte address mode
**/
BOOLEAN
EFIAPI
Is4ByteAddressMode()
{
    return (InternalCheckSpiFlashAddressMode() == FOUR_BYTE_ADDR_MODE) ? TRUE : FALSE;
}

/**
    This function check 64K erase commnad is available.

    @retval TRUE 64K erase commnad is available
    @retval FALSE 64K erase commnad is not available
**/
BOOLEAN
EFIAPI
IsErase64KAvailable(
    VOID
)
{
    if( gExFlashPart.FlashCommandMenu.Erase64K.Opcode == SPI_INVALID_COMMAND )
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/**
    This function sync SPI flash addressing mode with the platform configuration.

    @retval TRUE Now is in 4 byte address mode
    @retval FALSE Now is in 3 byte address mode
**/
VOID
EFIAPI
SyncSpiFlashAddressMode(
    IN  UINT32  FlashId
)
{
    // check the platform SPI address mode and update to SPI flash
    if( IsPlatformLanuchedOn4ByteAddress() )
    {
        SwitchSpiFlashAddressMode( FlashId, FOUR_BYTE_ADDR_MODE );
    }
    else
    {
        SwitchSpiFlashAddressMode( FlashId, THREE_BYTE_ADDR_MODE );
    }
}

/**
    This routine send write enable command.

    @retval UINT8 SPI flash status
**/
UINT8
CommonSpiReadStatus(
    VOID
)
{
    UINT8   Command;

    Command = gExFlashPart.FlashCommandMenu.ReadStatus.Opcode;
    ResetInternalFIFOPointer ();
    *(volatile UINT8*)gSpiBase = Command;
    // TxByte = 1, RxByte = 2
    SpiTxRxByteCount( (0x02 << 8) + 0x01 );
    ResetInternalFIFOPointer();
    *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_0) = 0;
    ResetInternalFIFOPointer();
    ExecuteSpiCommand();
    WaitForSpiCycleDone();
    ResetInternalFIFOPointer();
    Command = *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_1); 
    return Command;
}

/**
    This routine wait write command is completed.
**/
VOID
WaitForWriteOperationCompleted(
    VOID
)
{
    UINT16  WaitStsRetry;
    UINT8   Status;

    for( WaitStsRetry = 0; WaitStsRetry < 0xFFFF; WaitStsRetry++ )
    {
        // read flash status register.
        Status = CommonSpiReadStatus();
        // Is operation busy ?
        if( !(Status & 0x1) )
            break;
    }
}

/**
    Routine for Write SPI Status Register.

    @param WriteData Status to be written to SPI.
    @param OpcodeIndex Write status command. 
    @param IsDataPhase
    @param PrefixOp Command be sent before write status.
    @param SectorAddress
**/
VOID
CommonSpiWriteStatus(
    IN  UINT8   WriteData,
    IN  UINT8   OpcodeIndex,
    IN  UINT8   IsDataPhase,
    IN  UINT8   PrefixOp,
    IN  UINT32  SectorAddress
)
{
    UINT8   Command;

    if( PrefixOp )
    {
        Command = gExFlashPart.FlashCommandMenu.WriteStatusEnable.Opcode;
        *(volatile UINT8*)gSpiBase = Command;
        // TxByte = 0, RxByte = 0
        SpiTxRxByteCount( 0 );
        ExecuteSpiCommand();
        WaitForSpiCycleDone();
    }
    else
        SpiWriteEnable();
    ResetInternalFIFOPointer();
    *(volatile UINT8*)gSpiBase = OpcodeIndex;
    // TxByte = 1, RxByte = 0
    SpiTxRxByteCount( 1 );
    ResetInternalFIFOPointer();
    if( IsDataPhase )
        *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_0) = WriteData;
    ResetInternalFIFOPointer();
    ExecuteSpiCommand();
    WaitForSpiCycleDone();
    if( IsDataPhase )
        WaitForWriteOperationCompleted();
}

/**
    Routine for Write SPI Status Register-1 and Status Register-2.

    @param bWriteData Status to be written to SPI.
    @param OpcodeIndex Write status command. 
    @param IsDataPhase
    @param PrefixOp Command be sent before write status.
    @param SectorAddress
**/
VOID
CommonSpiWriteStatusTwoBytes(
    IN  UINT8   WriteData1,
    IN  UINT8   WriteData2,
    IN  UINT8   OpcodeIndex,    
    IN  UINT8   PrefixOp,
    IN  UINT32  SectorAddress
)
{
    UINT8   Command;

    if( PrefixOp )
    {
        Command = gExFlashPart.FlashCommandMenu.WriteStatusEnable.Opcode;
        *(volatile UINT8*)gSpiBase = Command;
        // TxByte = 0, RxByte = 0
        SpiTxRxByteCount( 0 );
        ExecuteSpiCommand();
        WaitForSpiCycleDone();
    }
    else
        SpiWriteEnable();
    ResetInternalFIFOPointer();
    *(volatile UINT8*)gSpiBase = OpcodeIndex;
    // TxByte = 1, RxByte = 0
    SpiTxRxByteCount( 2 );
    ResetInternalFIFOPointer();
    *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_0) = WriteData1;
    *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_1) = WriteData2;
    ResetInternalFIFOPointer();
    ExecuteSpiCommand();
    WaitForSpiCycleDone();
    WaitForWriteOperationCompleted();
}

/**
    Routine for reading byte data from spi.

    @param ByteAddress Address to be read from.

    @retval UINT8 Byte data.
**/
UINT8
CommonSpiReadByte(
    IN  UINTN   ByteAddress
)
{
    if( CommonConvertToSpiRomMmioAddress( ByteAddress, (VOID**)&ByteAddress ) == FALSE )
    {
        // ByteAddress is a flash memory address(0x0 ~ (Flash size -1))
        // Read a byte with SPI controller
        UINT8   Byte;
        UINT32  Length = 1;
        CommonSpiReadBytes( (volatile UINT8*)ByteAddress, &Byte, &Length );
        return Byte;
    }
    // ByteAddress is a MMIO address((0xFFFFFFFF - BIOS size + 1) ~ 0xFFFFFFFF)
    // Read a byte via MMIO
    return ( *(volatile UINT8*)ByteAddress );
}

/**
    Verifies if the device has been erased properly or if the current byte
    is the same as the byte to be written at this location.

    @param Destination starting address of where the data will be written
    @param Source starting address of the data that is supposed to be written or
        "NULL" for checking erase completed.
    @param Length length of the data set to check
    @param SpiCycle use the "SPI Cycle" or not
    @param IsMappedAddress Input param Destination is mapping address or not

    @retval TRUE the data is match or is clean.
    @retval FALSE the data is not match or is not clean.
**/
static
BOOLEAN
IsEqualOrClean(
    IN  volatile UINT8  *Destination,
    IN  UINT8           *Source,
    IN  UINT32          Length,
    IN  BOOLEAN         SpiCycle,
    IN  BOOLEAN         IsMappedAddress
)
{
    UINT8   Buffer[SPI_MAX_DATA_TRANSFER];
    UINT8   Data;
    UINT32  Index1;
    UINT32  Index2;
    UINT32  RemainBytes = Length;
    UINT32  ReadSize;

    for( Index1 = 0; Index1 < Length; Index1 += ReadSize, RemainBytes -= ReadSize )
    {
        // Initial local read buffer.
        SetMem( (VOID*)Buffer, SPI_MAX_DATA_TRANSFER, 0 );
        // Read flash through SPI Cycle if SpiCycle is requested.
        if( RemainBytes >= SPI_MAX_DATA_TRANSFER )
            ReadSize = SPI_MAX_DATA_TRANSFER;
        else
            ReadSize = RemainBytes;

        if( SpiCycle )
        {
            UINT32  TempSize = ReadSize;
            CommonSpiReadCommand( Destination + Index1, Buffer, &TempSize, IsMappedAddress );
            ReadSize -= TempSize;
        }
        else
            CopyMem( (VOID*)Buffer, (VOID*)(Destination + Index1), ReadSize );

        // Verify whether flash contents is the same as written Data or is clean.
        for( Index2 = 0; Index2 < ReadSize; Index2++ )
        {
            Data = (Source != NULL) ? *(Source + Index1 + Index2) : (UINT8)(-FLASH_ERASE_POLARITY);
            if( Buffer[Index2] != Data )
                return FALSE;
        }
    }

    return TRUE;
}

/**
    Convert spi address

    @param Address Address to be converted.

    @retval UINT32 Address.
**/
UINT32
CommonConvertSpiAddress(
    IN  volatile UINT8  *Address
)
{
    if( IsValidSpiRomOffset( (UINTN)Address ) == TRUE )
    {
        //In this case, the address won't map to 0xFF000000~0xFFFFFFFF, so use the offset directly
        return ((UINT32)(UINTN)Address);
    }

    if( gDeviceVirtual )
    {
        // Address - offset from Flash Device Base.
        Address -= gAmiFlashDeviceBase;
        // Address - 32bit memory mapping address.
        Address += (0xFFFFFFFF - FLASH_SIZE) + 1;
    }

    if( gIsSpiMmioAddressMappedBottom16M )
    {
        return (UINT32)((UINTN)Address & 0xFFFFFF);
    }

    return ((UINT32)(UINTN)Address);
}

/**
    Initialize spi
**/
VOID
InitializeSpiEnvironment(
    IN  FLASH_INFO  *FlashInfo
)
{
    return;
}

/**
    Re-initialize spi
**/
VOID
ReinitializeSpiEnvironment(
    IN  FLASH_INFO  *FlashInfo
)
{
    SyncSpiFlashAddressMode( (UINT32)gFlashId );

    return;
}

/**
    Read flash part's ID

    @param FlashInfo Pointer of FLASH_INFO structure.
    @param FlashId Pointer to return flash part's id.

    @retval TRUE Read id successfully.
**/
BOOLEAN
CommonSpiReadId(
    IN  FLASH_INFO  *FlashInfo,
    OUT UINT32      *FlashId
)
{
    UINT8   Command;

    CommonSpiDeviceWriteEnable();
    InitializeSpiEnvironment( FlashInfo );
    Command = FlashInfo->ReadId.Opcode;
    ResetInternalFIFOPointer();
    *(volatile UINT8*)gSpiBase = Command;
    if( Command != 0x9F )
    {
        // TxByte = 3, RxByte = 4
        SpiTxRxByteCount( (0x04 << 8) + 0x03 );
        ResetInternalFIFOPointer();
        *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_0) = 0;
        *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_1) = 0;
        *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_2) = 0;
    }
    else
    {
        // TxByte = 0, RxByte = 3
        SpiTxRxByteCount( (0x03 << 8) + 0 );
    }
    ResetInternalFIFOPointer();
    ExecuteSpiCommand();
    WaitForSpiCycleDone();
    ResetInternalFIFOPointer();
    if( Command != 0x9F )
        *FlashId = (*(volatile UINT32*)(gSpiBase + FIFO_ADDRESS_3) & (UINT32)0xFFFF);
    else
        *FlashId = (*(volatile UINT32*)(gSpiBase + FIFO_ADDRESS_0) & (UINT32)0xFFFFFF);

    CommonSpiDeviceWriteDisable();
    return TRUE;
}

/**
    This API function erases a block in the flash. Flash model specific code
    will branch out from this routine

    @param BlockAddress Block that need to be erased
    @param Length Number of bytes that need to be erased
    @param IsMappedAddress Input param BlockAddress is mapping address or not

    @retval EFI_SUCCESS erase complete
    @retval EFI_DEVICE_ERROR erase not completed
**/
EFI_STATUS
EFIAPI
CommonSpiEraseCommandEx(
    IN  volatile UINT8  *BlockAddress,
    IN  UINT32          Length,
    IN  BOOLEAN         IsMappedAddress
)
{
    volatile UINTN  SectorAddr;
    volatile UINTN  PhysicalAddr;
    UINT16          EraseRetry;
    UINT8           Command;
    BOOLEAN         IsClean;
    UINT32          ProcessLength;
    UINT32          CompleteLength;
    static BOOLEAN  TryErase64K = TRUE;
    BOOLEAN         Is4ByteAddrCmd = FALSE;
    BOOLEAN         Is4ByteAddrMode = FALSE;

    InitializeSpiEnvironment( &gExFlashPart.FlashCommandMenu );
    Is4ByteAddrMode = Is4ByteAddressMode();
    if( Length % gFlashApi->FlashSectorSize )
        return EFI_INVALID_PARAMETER;

    //Ensure the starting address of Blocks is aligned on boundary of ERASE (sub)sector size.
    if( (UINT32)(UINTN)BlockAddress % gFlashApi->FlashSectorSize != 0 )
        return EFI_INVALID_PARAMETER;

    SectorAddr = (UINTN)BlockAddress;
    CompleteLength = 0;
    //Check 64K earase command available
    if( TryErase64K == TRUE )
    {
        TryErase64K = IsErase64KAvailable();
    }

    for( ; CompleteLength < Length; SectorAddr += ProcessLength, CompleteLength += ProcessLength )
    {
        if( (TryErase64K == TRUE) &&
            (SectorAddr % SECTOR_SIZE_64KB == 0) &&
            ((Length - CompleteLength) >= SECTOR_SIZE_64KB) )
        {
            //If 64K earase command is available,
            //address is alignment on 64K and rest length is large than 64K
            ProcessLength = SECTOR_SIZE_64KB;
        }
        else
        {
            //Other cases keep using 4K erase
            ProcessLength = SECTOR_SIZE_4KB;
        }

        if( IsMappedAddress == TRUE )
            PhysicalAddr = CommonConvertSpiAddress( (volatile UINT8*)SectorAddr );
        else
            PhysicalAddr = SectorAddr;

        IsClean = IsEqualOrClean(
                    (volatile UINT8*)SectorAddr,
                    NULL,
                    ProcessLength,
                    TRUE,
                    IsMappedAddress );
        if( IsClean == TRUE )
            continue;

        SpiWriteEnable();
        Command = gExFlashPart.FlashCommandMenu.Erase.Opcode;
        if( (gFlashApi->FlashSectorSize == SECTOR_SIZE_64KB) ||
            (ProcessLength == SECTOR_SIZE_64KB) )
        {
            Command = gExFlashPart.FlashCommandMenu.Erase64K.Opcode;
        }

        Is4ByteAddrCmd = ConvertTo4ByteAddressCommandSet(
                            (UINT32)SectorAddr,
                            ProcessLength,
                            SPI_ERASE,
                            &Command );
        for( EraseRetry = 0; EraseRetry < FLASH_RETRIES; EraseRetry++ )
        {
            if( Is4ByteAddrMode || Is4ByteAddrCmd )
            {
            // TxByte = 4, RxByte = 0
                SpiTxRxByteCount( 4 );
                ResetInternalFIFOPointer();
                *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_0) = \
                                    (UINT8)((PhysicalAddr >> 24) & 0xFF );//A3;
                *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_1) = \
                                    (UINT8)((PhysicalAddr >> 16) & 0xFF );//A2;
                *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_2) = \
                                    (UINT8)((PhysicalAddr >> 8) & 0xFF );//A1;
                *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_3) = \
                                    (UINT8)(PhysicalAddr & 0xFF);//A0;
            }
            else
            {
                // TxByte = 3, RxByte = 0
                SpiTxRxByteCount( 3 );
                ResetInternalFIFOPointer();
                *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_0) = \
                                    (UINT8)((PhysicalAddr >> 16) & 0xFF);//A2;
                *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_1) = \
                                    (UINT8)((PhysicalAddr >> 8) & 0xFF);//A1;
                *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_2) = \
                                    (UINT8)(PhysicalAddr & 0xFF);//A0;
            }
            ResetInternalFIFOPointer();
            *(volatile UINT8*)gSpiBase = Command;
            ResetInternalFIFOPointer();
            ExecuteSpiCommand();
            WaitForSpiCycleDone();
            WaitForWriteOperationCompleted();
#if defined(ENABLE_ROM_CACHE_IN_DXE) && (ENABLE_ROM_CACHE_IN_DXE == 1)
            if( IsMappedAddress == TRUE )
            {
                // Flush the memory erased so that it will be read back correctly
                WriteBackInvalidateDataCacheRange( (VOID*)SectorAddr, ProcessLength );
                SpiFlashAsmMfence();
            }
            else
            {
                VOID    *MmioAddress;

                if( CommonConvertToSpiRomMmioAddress( PhysicalAddr, &MmioAddress ))
                {
                    WriteBackInvalidateDataCacheRange( MmioAddress, ProcessLength );
                    SpiFlashAsmMfence();
                }
            }
#endif
            IsClean = IsEqualOrClean(
                        (volatile UINT8*)SectorAddr,
                        NULL,
                        ProcessLength,
                        TRUE,
                        IsMappedAddress );
            if( IsClean == TRUE )
                break;
        }
        if( IsClean == FALSE )
        {
            if( ProcessLength == SECTOR_SIZE_64KB )
            {
                //If 64K erase failed, set ProcessLength to 0 and TryErase64K to FALSE
                //for erasing same address with 4K erase command
                ProcessLength = 0;
                TryErase64K = FALSE;
                continue;
            }
            return EFI_DEVICE_ERROR;
        }
    }

    return EFI_SUCCESS;
}

/**
    This API function erases a block in the flash. Flash model specific code
    will branch out from this routine

    @param BlockAddress Block that need to be erased                 
**/
BOOLEAN
EFIAPI
CommonSpiEraseCommand(
    IN  volatile UINT8  *BlockAddress
)
{
    return (EFI_ERROR(CommonSpiEraseCommandEx( BlockAddress, gFlashBlockSize, TRUE ))) ? FALSE : TRUE;
}

/**
    This function programs a byte data to the specified location

    @param Address Location where the data to be written
    @param Byte Byte to be written
    @param Length Number of bytes to write
    @param IsMappedAddress Input param Address is mapping address or not
**/
BOOLEAN
EFIAPI
CommonSpiProgramCommand(
    IN      volatile UINT8  *Address,
    IN      UINT8           *Byte,
    IN  OUT UINT32          *Length,
    IN      BOOLEAN         IsMappedAddress
)
{
    UINT8   FlashRetry;
    UINT8   Command;
    UINT16  ProgBytes;
    UINT16  NumBytes;
    UINT16  MaxNumBytes;
    UINT32  PhyAddress;
    BOOLEAN Is4ByteAddrCmd = FALSE;
    BOOLEAN Is4ByteAddrMode = FALSE;

    InitializeSpiEnvironment( &gExFlashPart.FlashCommandMenu );
    Is4ByteAddrMode = Is4ByteAddressMode();
    ProgBytes = (UINT16)gCommonSpiFlash.FlashProgramSize;
    if( gCommonSpiFlash.FlashProgramSize != 1 )
    {
        // Limit the max transfer to the number of bytes the chipset can
        // transfer per cycle
        if( *Length >= SPI_MAX_DATA_TRANSFER )
            ProgBytes = SPI_MAX_DATA_TRANSFER;
        else
            ProgBytes = (UINT16)(*Length);
        // this is currently for the WINBOND parts only
        // mask off lowest 8 bits of address so that we can determine how
        // many bytes we can write before we hit the end of a page
        MaxNumBytes = 0x100 - ((UINT32)(UINTN)Address & 0xFF);
        if( (UINT32)(UINTN)Address & 0x1 )
            ProgBytes = 1;
        else if( (UINT16)ProgBytes > MaxNumBytes )
            ProgBytes = MaxNumBytes;
    }
    for( FlashRetry = 0; FlashRetry < FLASH_RETRIES; FlashRetry++ )
    {
        //Skip to program if input buffer is clean
        if( IsEqualOrClean( (volatile UINT8*)Byte, NULL, ProgBytes, FALSE, FALSE ) )
            break;

        SpiWriteEnable();
        Command = gExFlashPart.FlashCommandMenu.Write.Opcode;
        Is4ByteAddrCmd = ConvertTo4ByteAddressCommandSet(
                            (UINT32)(UINTN)Address,
                            (UINT32)ProgBytes,
                            SPI_PROGRAM,
                            &Command );
        if( IsMappedAddress == TRUE )
            PhyAddress = CommonConvertSpiAddress ( Address );
        else
            PhyAddress = (UINT32)(UINTN)Address;
        if( Is4ByteAddrMode || Is4ByteAddrCmd )
        {
            // TxByte = Program Bytes + Address Bytes, RxByte = 0
            SpiTxRxByteCount( ProgBytes + 4 );
            ResetInternalFIFOPointer();
            *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_0) = \
                                (UINT8)((PhyAddress >> 24) & 0xFF);//A3;
            *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_1) = \
                                (UINT8)((PhyAddress >> 16) & 0xFF);//A2;
            *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_2) = \
                                (UINT8)((PhyAddress >> 8) & 0xFF);//A1;
            *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_3) = \
                                (UINT8)(PhyAddress & 0xFF);//A0;
            for( NumBytes = 0; NumBytes < ProgBytes; NumBytes++ )
            {
#if defined(REG80_FIFO_SUPPORT) && (REG80_FIFO_SUPPORT == 1)
                *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_4 + NumBytes) = *(Byte + NumBytes);
#else
                *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_4) = *(Byte + NumBytes);
#endif
            }
        }
        else
        {
            // TxByte = Program Bytes + Address Bytes, RxByte = 0
            SpiTxRxByteCount( ProgBytes + 3 );
            ResetInternalFIFOPointer();
            *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_0) = \
                                (UINT8)((PhyAddress >> 16) & 0xFF);//A2;
            *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_1) = \
                                (UINT8)((PhyAddress >> 8) & 0xFF);//A1;
            *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_2) = \
                                (UINT8)(PhyAddress & 0xFF);//A0;
            for( NumBytes = 0; NumBytes < ProgBytes; NumBytes++ )
            {
#if defined(REG80_FIFO_SUPPORT) && (REG80_FIFO_SUPPORT == 1)
                *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_3 + NumBytes) = *(Byte + NumBytes);
#else
                *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_3) = *(Byte + NumBytes);
#endif
            }
        }
        ResetInternalFIFOPointer();
        *(volatile UINT8*)gSpiBase = Command;
        ResetInternalFIFOPointer();
        ExecuteSpiCommand();
        // wait for chipset SPI flash operation completed.
        WaitForSpiCycleDone();
        WaitForWriteOperationCompleted();
#if defined(ENABLE_ROM_CACHE_IN_DXE) && (ENABLE_ROM_CACHE_IN_DXE == 1)
        if( IsMappedAddress == TRUE )
        {
            // Flush the memory erased so that it will be read back correctly
            WriteBackInvalidateDataCacheRange( (VOID*)Address, ProgBytes );
            SpiFlashAsmMfence();
        }
        else
        {
            VOID    *MmioAddress;

            if( CommonConvertToSpiRomMmioAddress( (UINTN)PhyAddress, &MmioAddress ))
            {
                WriteBackInvalidateDataCacheRange( MmioAddress, ProgBytes );
                SpiFlashAsmMfence();
            }
        }
#endif
        // write operation appeared to succeed, now read back byte and compare
        // set control for 1-byte data read, no prefix
        if( IsEqualOrClean( Address, Byte, ProgBytes, TRUE, IsMappedAddress ) )
            break;
        if( FLASH_RETRIES == (FlashRetry + 1) )
            return FALSE;
    }
    // Don't forget to return the number of bytes not written
    *Length = *Length - (UINT32)ProgBytes;
    return TRUE;
}

/**
    This function read bytes data to the specified location by directly sending SPI command, not MMIO read.

    @param ByteAddress Location where the data to be read.
    @param Byte Data to be read.
    @param Length Number of bytes to read
**/
VOID
CommonSpiReadBytes(
    IN      volatile UINT8  *ByteAddress,
    OUT     UINT8           *Byte,
    IN  OUT UINT32          *Length
)
{
    UINT8   Command;
    UINT16  ProgBytes = 0;
    UINT16  NumBytes = 0;
    UINT32  PhyAddress = 0;
    UINT32  TotalProgBytes;
    BOOLEAN Is4ByteAddrMode = FALSE;
    BOOLEAN Is4ByteAddrCmd = FALSE;

    InitializeSpiEnvironment( &gExFlashPart.FlashCommandMenu );
    Is4ByteAddrMode = Is4ByteAddressMode();

    ProgBytes = 0;

    for( TotalProgBytes = 0; TotalProgBytes < *Length ; TotalProgBytes += ProgBytes )
    {
        // Limit the max transfer to the number of bytes the chipset can
        // transfer per cycle
        if( (*Length - TotalProgBytes) >= SPI_MAX_DATA_TRANSFER )
            ProgBytes = SPI_MAX_DATA_TRANSFER;
        else
            ProgBytes = (UINT16)(*Length - TotalProgBytes);

        Command = gExFlashPart.FlashCommandMenu.Read.Opcode;
        // Here ByteAddress is a flash memory address, don't need to do the address conversion.
        PhyAddress = CommonConvertSpiAddress( (UINT8 *)(ByteAddress + (UINTN)TotalProgBytes) );
        Is4ByteAddrCmd = ConvertTo4ByteAddressCommandSet(
                            (UINT32)(UINTN)ByteAddress,
                            *Length,
                            SPI_READ,
                            &Command );
        if( Is4ByteAddrMode || Is4ByteAddrCmd )
        {
            // TxByte = Program Bytes + Address Bytes, RxByte = 0
            SpiTxRxByteCount( (ProgBytes << 8) + 4 );
            ResetInternalFIFOPointer();
            *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_0) = \
                                (UINT8)((PhyAddress >> 24) & 0xFF);//A3;
            *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_1) = \
                                (UINT8)((PhyAddress >> 16) & 0xFF);//A2;
            *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_2) = \
                                (UINT8)((PhyAddress >> 8) & 0xFF);//A1;
            *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_3) = \
                                (UINT8)(PhyAddress & 0xFF);//A0;
        }
        else
        {
            // TxByte = Program Bytes + Address Bytes, RxByte = 0
            SpiTxRxByteCount( (ProgBytes << 8) + 3 );
            ResetInternalFIFOPointer();
            *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_0) = \
                                (UINT8)((PhyAddress >> 16) & 0xFF);//A2;
            *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_1) = \
                                (UINT8)((PhyAddress >> 8) & 0xFF);//A1;
            *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_2) = \
                                (UINT8)(PhyAddress & 0xFF);//A0;
        }
        ResetInternalFIFOPointer();
        *(volatile UINT8*)gSpiBase = Command;
        ExecuteSpiCommand();
        // wait for chipset SPI flash operation completed.
        WaitForSpiCycleDone();
        if( Is4ByteAddrMode || Is4ByteAddrCmd )
        {
            for( NumBytes = 0; NumBytes < ProgBytes; NumBytes++ )
            {
#if defined(REG80_FIFO_SUPPORT) && (REG80_FIFO_SUPPORT == 1)
                *(Byte + TotalProgBytes + NumBytes) = *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_4 + NumBytes);
#else
                *(Byte + TotalProgBytes + NumBytes) = *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_4);
#endif
            }
        }
        else
        {
            for( NumBytes = 0; NumBytes < ProgBytes; NumBytes++ )
            {
#if defined(REG80_FIFO_SUPPORT) && (REG80_FIFO_SUPPORT == 1)
                *(Byte + TotalProgBytes + NumBytes) = *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_3 + NumBytes);
#else
                *(Byte + TotalProgBytes + NumBytes) = *(volatile UINT8*)(gSpiBase + FIFO_ADDRESS_3);
#endif
            }
        }
    }
    // Don't forget to return the number of bytes not written
    *Length = 0;
    return;
}

/**
    This function read data from the specified location

    @param Address Location where the data to be read
    @param Byte Data buffer to be read
    @param Length Number of bytes to read
    @param IsMappedAddress Input param Address is mapping address or not
**/
VOID
EFIAPI
CommonSpiReadCommand(
    IN      volatile UINT8  *Address,
    OUT     UINT8           *Byte,
    IN  OUT UINT32          *Length,
    IN      BOOLEAN         IsMappedAddress
)
{
    UINTN   ReadAddress;
    UINTN   Index;

    ReadAddress = (UINTN)Address;

    if( IsMappedAddress == FALSE )
    {
        //Address is part offset
        if( CommonConvertToSpiRomMmioAddress( ReadAddress, (VOID**)&ReadAddress ) == FALSE )
        {
            //Convert offset to address failed
            CommonSpiReadBytes( Address, Byte, Length );
            return;
        }
    }

    //Address is a MMIO address((0xFFFFFFFF - BIOS size + 1) ~ 0xFFFFFFFF)
    for( Index = 0; Index < *Length ; Index++ )
    {
        *(Byte + Index) = CommonSpiReadByte( ReadAddress + Index );
    }

    *Length = 0;
}

/**
    This function writes the status register by specified flash address

    @param FlashOffset Offset to access flash part
    @param Length Length to access flash part
    @param StatusData Data to be written to the status register.
**/
VOID
SpiBlockProtectUpdate(
    IN  UINT32  FlashOffset,
    IN  UINT32  Length,
    IN  UINT8   StatusData
)
{
    UINT8   StatusReg;
    UINT8   PrefixOp;
    UINT8   BpBits;

    UINT8   OpmenuIndex;

    StatusReg = CommonSpiReadStatus();
    OpmenuIndex = gExFlashPart.FlashCommandMenu.WriteStatus.Opcode;

    // default flash, prefix 0 w/o address
    BpBits = (BIT2 + BIT3 + BIT4);
    PrefixOp = SPI_PREFIX_WRITE_EN;
    switch( (UINT8)gExFlashPart.FlashVenDevId )
    {
        // if SST flash, prefix 1 w/o address
        case 0xBF :
            PrefixOp = SPI_PREFIX_WRITE_S_EN;
            break;
        // if ATMEL flash, prefix 0 w/ address
        case 0x1F :
            BpBits = (BIT2 + BIT3);
            break;
        // if GigaDevice flash
        case 0xC8 :
            switch( (UINT16)gExFlashPart.FlashVenDevId )
            {
                // change BP bits to 0x7C(BP0~BP4) for the following flash parts...
                // 0x40C8 - GD25QXXD
                // 0x60C8 - GD25LBXXD
                // 0x67C8 - GD25LRXXE, GD25LBXXE
                case 0x40C8 :
                case 0x60C8 :
                case 0x67C8 :
                    BpBits = (BIT2 | BIT3 | BIT4 | BIT5 | BIT6);
                break;
            }
            break;
        // if XMC flash
        case 0x20 :
            switch( (UINT16)gExFlashPart.FlashVenDevId )
            {
                // change BP bits to 0x3C(BP0~BP3) for the following flash parts...
                // 0x3820 - XM25QUXXA
                // 0x4320 - XM25RHXXC
                // 0x6020 - XM25QHXXB
                // 0x7020 - XM25QUXXB, XM25QHXXA
                case 0x3820 :
                case 0x4320 :
                case 0x6020 :
                case 0x7020 :
                    BpBits = (BIT2 | BIT3 | BIT4 | BIT5);
                    break;
                // change BP bits to 0x3C(BP0~BP3) for the following flash parts, 
                // 0x5020 - XM25QU64B(64M bits), XM25QU128B(128M bits)
                case 0x5020 : 
                    if( gExFlashPart.FlashCapacity >= (UINT32)SIZE_8MB)
                    {
                        BpBits = (BIT2 | BIT3 | BIT4 | BIT5);
                    }
                    break;
            }
            break;
        // if Winbond flash
        case 0xEF :
            switch( (UINT16)gExFlashPart.FlashVenDevId )
            {
                // change BP bits to 0x3C(BP0~BP3) for the following flash parts...
                // 0x40EF - W25Q256FV(256M bits), W25Q256JV(256M bits), W25Q256JV-IQ/JQ(256M bits), 
                //          W25Q256JW_DTR(256M bits), W25Q257JV(256M bits), W25Q257FV(256M bits)
                // 0x60EF - W25Q256JW(256M bits)
                // 0x70EF - W25Q256JV-DTR(256M bits), W25Q256JV-IM/JM(256M bits)
                // 0x80EF - W25Q256JW-IM(256M bits), W25Q256JW_DTR(256M bits)
                case 0x40EF :
                case 0x60EF :
                case 0x70EF :
                case 0x80EF :
                    if( gExFlashPart.FlashCapacity >= (UINT32)SIZE_32MB)
                    {
                        BpBits = (BIT2 | BIT3 | BIT4 | BIT5);
                    }
                    break;
            }
            break;
        // if MXIC flash
        case 0xC2 :
            switch( (UINT16)gExFlashPart.FlashVenDevId )
            {
                // change BP bits to 0x3C(BP0~BP3) for the following flash parts...
                // 0x24C2 - MX25LXX35D
                // 0x25C2 - 
                // 0x28C2 - MX25RXX35F
                // 0x75C2 - 
                case 0x24C2 :
                case 0x25C2 :
                case 0x28C2 :
                case 0x75C2 :
                    BpBits = (BIT2 | BIT3 | BIT4 | BIT5);
                    break;
                // change BP bits to 0x3C(BP0~BP3) for the following flash parts, 
                // 0x20C2 - MX25L3206E(32M bits)
                case 0x20C2 : 
                    if( gExFlashPart.FlashCapacity >= (UINT32)SIZE_4MB)
                    {
                        BpBits = (BIT2 | BIT3 | BIT4 | BIT5);
                    }
                    break;
            }
            break;
        // if ISSI flash
        case 0x9D :
            switch( (UINT16)gExFlashPart.FlashVenDevId )
            {
                // change BP bits to 0x7C(BP0~BP3) for the following flash parts...
                // 0x609D - IS25LPXXX
                // 0x709D - IS25WPXXX
                case 0x609D :
                case 0x709D :
                    BpBits = (BIT2 | BIT3 | BIT4 | BIT5);
                break;
            }
            break;
    }
    StatusReg &= BpBits;              // keep valid bits.
    StatusData &= BpBits;             // keep valid bits.
    if( StatusReg != StatusData )
    {
        UINT8   DataPhase = 1;

        StatusData |= (CommonSpiReadStatus() & ~BpBits);    // Preserve NON-BP bits and apply new BP bits
        CommonSpiWriteStatus(
            StatusData,
            OpmenuIndex,
            DataPhase,
            PrefixOp,
            FlashOffset );
    }
}

/**
    This function contains any flash specific code need to enable a
    particular flash block write

    @param BlockAddress Location where the block register to be set
    @param Length Length Length to access flash part
    @param IsMappedAddress Input param BlockAddress is mapping address or not
**/
VOID
EFIAPI
CommonSpiBlockWriteEnable(
    IN  volatile UINT8  *BlockAddress,
    IN  UINT32          Length,
    IN  BOOLEAN         IsMappedAddress
)
{
    SpiBlockProtectUpdate( 0, Length, 0 );
}

/**
    This function contains any flash specific code need to disable a 
    particular flash block write

    @param BlockAddress Location where the block register to be set
    @param Length Length Length to access flash part
    @param IsMappedAddress Input param BlockAddress is mapping address or not
**/
VOID
EFIAPI
CommonSpiBlockWriteDisable(
    IN  volatile UINT8  *BlockAddress,
    IN  UINT32          Length,
    IN  BOOLEAN         IsMappedAddress
)
{
#if defined(BLOCK_PROTECT_ENABLE) && (BLOCK_PROTECT_ENABLE == 1)
    SpiBlockProtectUpdate( 0, Length, 0xFF );
#endif
}

/**
    This function contains any flash specific code need to enable flash write.
**/
VOID
EFIAPI
CommonSpiDeviceWriteEnable(
    VOID
)
{
    // check is DeviceWrite enabled, if yes, don't enable it again,
    // else, enable it.
    if( !gDeviceWriteEnabled )
    {
        gDeviceWriteEnabled = 1;
    }
}

/**
    This function contains any flash specific code need to disable flash write.
**/
VOID
EFIAPI
CommonSpiDeviceWriteDisable(
    VOID
)
{
    // check is DeviceWrite enabled, if yes, disable it, if no, don't disable it.
    if( gDeviceWriteEnabled )
    {
        gDeviceWriteEnabled = 0;
    }
}

/**
    This function returns granularity.

    @param Granularity Pointer to supported granularity array
    @param NumberOfEntries Granularity array entries
**/
static BOOLEAN
EFIAPI
CommonSpiGetEraseGranularity(
    IN  OUT UINT32  **Granularity,
    IN  OUT UINT32  *NumberOfEntries
)
{
    if( (Granularity == NULL) || (NumberOfEntries == NULL) )
        return FALSE;

    //Initial first granularity with SPI identify's sector size
    *NumberOfEntries = 1;
    gGranularity[(*NumberOfEntries - 1)] = gCommonSpiFlash.FlashSectorSize;

    *Granularity = gGranularity;

    return TRUE;
}

/**
    This function will be invoked by the core to convert runtime
    pointers to virtual address.

    @param Rs Pointer to runtime services.
**/
static
VOID
EFIAPI
CommonSpiDeviceVirtualFixup(
    IN  EFI_RUNTIME_SERVICES    *Rs
)
{

//  // Following is an example code for virtual address conversion
//  pRS->ConvertPointer(0, (VOID**)&gAmiFlashDeviceBase);

    Rs->ConvertPointer(0, (VOID **)&gSpiBase);
    gDeviceVirtual = 1;

    return;
}
