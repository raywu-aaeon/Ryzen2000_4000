//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  extended SPI Flash library source file.
**/

//----------------------------------------------------------------------------
// Includes
#include <Uefi.h>
#include "Token.h"

#include <Library/AmiFlashLib.h>
#include "Library/ExtSpiFlashLib.h"

#include "ExtSpiFlash.h"
#include "FlashPart.h"
#include "SpiFlash.h"

#define     SPI_PREFIX_WRITE_S_EN       0x1
#define     SPI_PREFIX_WRITE_EN         0x0

#define SpiFlashAddress ((UINT32)0xFFFFFFFF - FLASH_SIZE + 1)

#define     THREE_BYTE_ADDR_MODE        ((UINT8)0x3)
#define     FOUR_BYTE_ADDR_MODE         ((UINT8)0x4)
#define     UNINITIALIZED_ADDR_MODE     ((UINT8)0xFF)
//----------------------------------------------------------------------------
// Module level global data
//----------------------------------------------------------------------------
extern  FLASH_PART      *gFlashApi;
extern  EX_FLASH_PART   gExFlashPart;
extern  volatile UINT8  *gSpiBase;

UINT32              gSupportedEarSpiFlashID = 0;
volatile UINT8      *gSpiFlashAddr = (UINT8*)(UINTN)SpiFlashAddress;

UINT8   gSavedAddressMode = UNINITIALIZED_ADDR_MODE;     // 0xFF uninitialized
UINT8   gSavedEar = 0;

//----------------------------------------------------------------------------
// Extern Function Prototypes
//----------------------------------------------------------------------------
extern  BOOLEAN EFIAPI SwitchSpiFlashAddressMode( IN  UINT32  FlashId, IN  UINT8   Mode );
extern  UINT8 EFIAPI GetSpiFlashAddressMode( IN  UINT32  FlashId );
#if defined(AMD_SPI_ROM_PROTECT) && (AMD_SPI_ROM_PROTECT == 1)
extern VOID AmdSpiRomProtectWriteEnable( VOID );
extern VOID AmdSpiRomProtectWriteDisable( VOID );
#endif

//----------------------------------------------------------------------------
// Flash Part Data Structures
//----------------------------------------------------------------------------

EXT_SPI_FLASH_FUNC_INFO gSupportedEarSpiFlashInfo[] = {
//--------------------------------------------------------------------------------------------------------------------------
//|        Device            |  ReadEAR   |  WriteEAR  |                                  |
//|          ID              |   OpCode   |   OpCode   |   Read EAR Funciton              |   EAR change Function 
//--------------------------------------------------------------------------------------------------------------------------
    { WINBOND_W25Q256FV,        0xC8,          0xC5,       CommonExtSpiFlashEarRead,          CommonExtSpiFlashEarChange},
    { WINBOND_W25Q256JW,        0xC8,          0xC5,       CommonExtSpiFlashEarRead,          CommonExtSpiFlashEarChange},
    { WINBOND_W25Q256JW_2,      0xC8,          0xC5,       CommonExtSpiFlashEarRead,          CommonExtSpiFlashEarChange},
    { WINBOND_W25Q256JV,        0xC8,          0xC5,       CommonExtSpiFlashEarRead,          CommonExtSpiFlashEarChange},
    { MX25L25633F,              0xC8,          0xC5,       CommonExtSpiFlashEarRead,          CommonExtSpiFlashEarChange},
    { MX25U25635F,              0xC8,          0xC5,       CommonExtSpiFlashEarRead,          CommonExtSpiFlashEarChange},
    { MX77U25650F,              0xC8,          0xC5,       CommonExtSpiFlashEarRead,          CommonExtSpiFlashEarChange},
    { MX77L25650F,              0xC8,          0xC5,       CommonExtSpiFlashEarRead,          CommonExtSpiFlashEarChange},
    { MT25QL256ABA,             0xC8,          0xC5,       CommonExtSpiFlashEarRead,          CommonExtSpiFlashEarChange},
    { MT25QL256ABA_2,           0xC8,          0xC5,       CommonExtSpiFlashEarRead,          CommonExtSpiFlashEarChange},
    { GD25R256D,                0xC8,          0xC5,       CommonExtSpiFlashEarRead,          CommonExtSpiFlashEarChange},
    { GD25LR256E,               0xC8,          0xC5,       CommonExtSpiFlashEarRead,          CommonExtSpiFlashEarChange},
    { XM25RH256C,               0xC8,          0xC5,       CommonExtSpiFlashEarRead,          CommonExtSpiFlashEarChange},
    { IS25LP256E,               0xC8,          0xC5,       IssiExtSpiFlashEarRead,            IssiExtSpiFlashEarChange},
    { IS25WP256E,               0xC8,          0xC5,       IssiExtSpiFlashEarRead,            IssiExtSpiFlashEarChange},
    { XM25QU256B,               0xC8,          0xC5,       IssiExtSpiFlashEarRead,            IssiExtSpiFlashEarChange},
    { 0, 0, 0, NULL, NULL}, //End of table
};

EXT_SPI_FLASH_FUNC_INFO gCurrentEarSpiFlashInfo = {0, 0, 0, NULL, NULL};

//----------------------------------------------------------------------------
// Functions Definitions
//----------------------------------------------------------------------------
VOID
ChipsetWriteEnable(
    OUT BOOLEAN *ProtectStatus
)
{
#if defined(AMD_SPI_ROM_PROTECT) && (AMD_SPI_ROM_PROTECT == 1)
    if( (*(gSpiBase + 0x9) != 0x6) || (*(gSpiBase + 0x2) & (BIT7 | BIT6)) )
    {
        //Restrict command doesn't have write enable instruction or
        //SpiHostAccessRomEn or SpiAccessMacRomEn bit doesn't be cleared
        *ProtectStatus = FALSE;
    }
    else
    {
        //Rom protect is enabled
        AmdSpiRomProtectWriteEnable();
        *ProtectStatus = TRUE;
    }
#endif
}

VOID
ChipsetWriteDisable(
    IN  BOOLEAN *ProtectStatus
)
{
#if defined(AMD_SPI_ROM_PROTECT) && (AMD_SPI_ROM_PROTECT == 1)
    if( *ProtectStatus == TRUE )
        AmdSpiRomProtectWriteDisable();
#endif
}

EFI_STATUS
EFIAPI
CommonExtSpiFlashEarRead (
    OUT UINT8     *SegmentIndex
)
{
    EFI_STATUS  Status;
    UINT8       OriOpCode;
    UINT8       CurrentEar = 0;

    Status = UpdateEarSpiFlashInfo();
    if (EFI_ERROR(Status)) return Status; 

    // read the current segment index of EAR register specified
    OriOpCode = gExFlashPart.FlashCommandMenu.ReadStatus.Opcode; //Save original Opcode
    gExFlashPart.FlashCommandMenu.ReadStatus.Opcode = gCurrentEarSpiFlashInfo.ReadEarOp;
    CurrentEar = CommonSpiReadStatus();
    gExFlashPart.FlashCommandMenu.ReadStatus.Opcode = OriOpCode; //Restore Opcode

    *SegmentIndex = CurrentEar;

    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
IssiExtSpiFlashEarRead (
    OUT UINT8     *SegmentIndex
)
{
    EFI_STATUS  Status;
    UINT8       OriOpCode;
    UINT8       CurrentEar = 0;

    Status = UpdateEarSpiFlashInfo();
    if (EFI_ERROR(Status)) return Status; 

    // read the current segment index of EAR register specified
    OriOpCode = gExFlashPart.FlashCommandMenu.ReadStatus.Opcode; //Save original Opcode
    gExFlashPart.FlashCommandMenu.ReadStatus.Opcode = gCurrentEarSpiFlashInfo.ReadEarOp;
    CurrentEar = CommonSpiReadStatus();
    gExFlashPart.FlashCommandMenu.ReadStatus.Opcode = OriOpCode; //Restore Opcode

    *SegmentIndex = (UINT8)(CurrentEar & 0x7F); // vaild bits [BIT6:BIT0], BIT7 is EXTADD

    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
CommonExtSpiFlashEarChange (
    UINT8     SegmentIndex
)
{
    EFI_STATUS  Status;
    BOOLEAN     PreviousStaus;

    Status = UpdateEarSpiFlashInfo();
    if (EFI_ERROR(Status)) return Status; 

    // 1. execute WRITE ENABLE command before a write register
    ChipsetWriteEnable( &PreviousStaus );
    // 2. execute WRITE EXTENDED ADDRESS REGISTER command to update EAR register
    CommonSpiWriteStatus(
        SegmentIndex,                       // input data
        gCurrentEarSpiFlashInfo.WriteEarOp, // WRITE EXTENDED ADDRESS REGISTER command
        1,
        SPI_PREFIX_WRITE_EN,                // prefix: WRITE ENABLE command
        0 );
    ChipsetWriteDisable( &PreviousStaus );

    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
IssiExtSpiFlashEarChange (
    UINT8     SegmentIndex
)
{
    EFI_STATUS  Status;
    UINT8       OriOpCode;
    UINT8       BankAddressReg = 0;
    BOOLEAN     PreviousStaus;

    Status = UpdateEarSpiFlashInfo();
    if (EFI_ERROR(Status)) return Status; 

    // read the current segment index of EAR register specified
    OriOpCode = gExFlashPart.FlashCommandMenu.ReadStatus.Opcode; //Save original Opcode
    gExFlashPart.FlashCommandMenu.ReadStatus.Opcode = gCurrentEarSpiFlashInfo.ReadEarOp;
    BankAddressReg = CommonSpiReadStatus();
    gExFlashPart.FlashCommandMenu.ReadStatus.Opcode = OriOpCode; //Restore Opcode

    // vaild bits [BIT6:BIT0], BIT7 is EXTADD
    BankAddressReg = (BankAddressReg & (UINT8)0x80) | SegmentIndex;

    // 1. execute WRITE ENABLE command before a write register
    ChipsetWriteEnable( &PreviousStaus );
    // 2. execute WRITE EXTENDED ADDRESS REGISTER command to update EAR register
    CommonSpiWriteStatus(
        BankAddressReg,                     // input data
        gCurrentEarSpiFlashInfo.WriteEarOp, // WRITE EXTENDED ADDRESS REGISTER command
        1,
        SPI_PREFIX_WRITE_EN,                // prefix: WRITE ENABLE command
        0 );
    ChipsetWriteDisable( &PreviousStaus );

    return EFI_SUCCESS;
}

/**
    Initialize the extended SPI libarary

    None

    @retval EFI_SUCCESS           Request portion are protected.
    @retval EFI_UNSUPPORTED       Current SPI flash device is not supported.
**/
EFI_STATUS
UpdateEarSpiFlashInfo(
    VOID
)
{
    UINTN   Index;

    if( gSupportedEarSpiFlashID == 0xFFFFFFFF )
        return EFI_UNSUPPORTED;

    if( gFlashApi == NULL )
        AmiFlashInit();

    if( gFlashApi == NULL )
    {
        gSupportedEarSpiFlashID = 0xFFFFFFFF; ////Indicate not supported Spi Flash
        return EFI_UNSUPPORTED;
    }

    if( !gSupportedEarSpiFlashID )
    {
        gSupportedEarSpiFlashID = gExFlashPart.FlashVenDevId;
        Index = 0;
        //Is onboard SPI Flash on supported list?
        do
        {
            if( gSupportedEarSpiFlashID == gSupportedEarSpiFlashInfo[Index].SpiDeviceId)
            {
                //Give correct value for block protection
                gCurrentEarSpiFlashInfo = gSupportedEarSpiFlashInfo[Index];
                return EFI_SUCCESS;
            }
            Index++;
        }while( gSupportedEarSpiFlashInfo[Index].SpiDeviceId );
        gSupportedEarSpiFlashID = 0xFFFFFFFF; //Indicate not supported Spi Flash
        return EFI_UNSUPPORTED;
    }
    else
    {
        //Make sure the current Spi Flash information was updated correctly
        if( gCurrentEarSpiFlashInfo.SpiDeviceId == gSupportedEarSpiFlashID )
            return EFI_SUCCESS;
        else
            return EFI_UNSUPPORTED;
    }
}

/**
    Read current specified segment(128Mbit).

    @param SegmentIndex, points to a buffer for receiveing current segment index

    @retval EFI_SUCCESS           Swtich to the specific segment successfully
    @retval EFI_UNSUPPORTED       Current SPI flash device is not supported.
    @retval EFI_DEVICE_ERROR      Operation aborted because of device limitation
**/
EFI_STATUS
EFIAPI
GetCurrent128MbSegment(
    OUT  UINT8    *SegmentIndex
)
{
    EFI_STATUS  Status; 

    Status = UpdateEarSpiFlashInfo();
    if( EFI_ERROR(Status) )
        return Status; 

    if( gCurrentEarSpiFlashInfo.ExtSpiFlashEarRead )
        return gCurrentEarSpiFlashInfo.ExtSpiFlashEarRead( SegmentIndex );
    else
        return EFI_UNSUPPORTED;
}

/**
    Switch to the specific segment(128Mbit).

    @param SegmentIndex, 0x0 is 1st(lowest) 128Mbit segment, 0x1 is 2nd 128Mbit(upper) segment.

    @retval EFI_SUCCESS           Swtich to the specific segment successfully
    @retval EFI_UNSUPPORTED       Current SPI flash device is not supported.
    @retval EFI_DEVICE_ERROR      Operation aborted because of device limitation
**/
EFI_STATUS
EFIAPI
Switch128MbSegment(
    IN  UINT8    SegmentIndex
)
{
    EFI_STATUS  Status; 

    Status = UpdateEarSpiFlashInfo();
    if( EFI_ERROR(Status) )
        return Status;

    if( gCurrentEarSpiFlashInfo.ExtSpiFlashEarChange )
        return gCurrentEarSpiFlashInfo.ExtSpiFlashEarChange( SegmentIndex );
    else
        return EFI_UNSUPPORTED;
}

UINT8 
CheckEAR(
    VOID
)
{
    UINT8   EarValue;

    GetCurrent128MbSegment( &EarValue );

    return EarValue;
}

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

    @param Area - TRUE:TOP 16M 
                  FALSE:Bottom 16M 
                  
    @return EFI_STATUS             
**/
VOID
SwitchFlashArea(
    IN  BOOLEAN Area
)
{
    // SPI Address mode transition with SwitchFlashArea()
    // 
    // A. Bottom BIOS(is booting) call SwitchFlashArea() while the device is in 3-byte address mode(3-BYTE)
    // calls    before SwitchFlashArea()    after SwitchFlashArea()     "gSavedAddressMode" after SwitchFlashArea() 
    //   1          (3-BYTE)                    (3-BYTE)                UNINITIALIZED_ADDR_MODE
    //   2          (3-BYTE)                    (3-BYTE)                UNINITIALIZED_ADDR_MODE
    //   3          (3-BYTE)                    (3-BYTE)                UNINITIALIZED_ADDR_MODE
    //   4          (3-BYTE)                    (3-BYTE)                UNINITIALIZED_ADDR_MODE
    //  ...
    // B. Top BIOS(is booting) call SwitchFlashArea() while the device is in 4-byte address mode(4-BYTE)
    // calls    before SwitchFlashArea()    after SwitchFlashArea()     "gSavedAddressMode" after SwitchFlashArea() 
    //   1          (4-BYTE)                    (3-BYTE)                FOUR_BYTE_ADDR_MODE
    //   2          (3-BYTE)                    (4-BYTE)                UNINITIALIZED_ADDR_MODE
    //   3          (4-BYTE)                    (3-BYTE)                FOUR_BYTE_ADDR_MODE
    //   4          (3-BYTE)                    (4-BYTE)                UNINITIALIZED_ADDR_MODE
    // ...

    // check the current address mode and swtich to 3 bytes address mode if 4 bytes address mode is active.
    if( gSavedAddressMode == UNINITIALIZED_ADDR_MODE )
    {
        if( CheckSpiFlashAddressMode() == FOUR_BYTE_ADDR_MODE )
        {
            ChangeSpiFlashAddressMode( THREE_BYTE_ADDR_MODE );
            *(volatile UINT8*)(gSpiBase + 0x50) = 0;
            *(volatile UINT8*)(gSpiBase + 0x5C) = 0;
            gSavedAddressMode = FOUR_BYTE_ADDR_MODE;
            gSavedEar = CheckEAR();
        }
        if( Area == TRUE )
        {
            Switch128MbSegment( 1 );
        }
        else
        {
            Switch128MbSegment( 0 );
        }
    }
    else
    {
        if( CheckSpiFlashAddressMode() == FOUR_BYTE_ADDR_MODE )
        {
            return; // switch failed, should not come here.
        }
        if( Area == TRUE )
        {
            Switch128MbSegment( 1 );
        }
        else
        {
            Switch128MbSegment( 0 );
        }
        // swtich to the previous mode(FOUR_BYTE_ADDR_MODE) because the current mode is caused by the previous call.
        if( gSavedAddressMode == FOUR_BYTE_ADDR_MODE )
        {
            Switch128MbSegment( gSavedEar );
            ChangeSpiFlashAddressMode( FOUR_BYTE_ADDR_MODE );
            *(volatile UINT8*)(gSpiBase + 0x50) |= BIT0;
            *(volatile UINT8*)(gSpiBase + 0x5C) |= BIT0;
            gSavedAddressMode = UNINITIALIZED_ADDR_MODE;
        }
    }
}

/**
    This function change SPI flash addressing mode to 3 or 4 bytes address mode.

    @param Mode THREE_BYTE_ADDR_MODE or FOUR_BYTE_ADDR_MODE

    @retval TRUE Successfully change mode 
    @retval FALSE Failed to change mode or changing addressing mode is not supproted by device
**/
BOOLEAN
EFIAPI
ChangeSpiFlashAddressMode(
    IN  UINT8   Mode
)
{
    EFI_STATUS  Status; 

    Status = UpdateEarSpiFlashInfo();
    if( EFI_ERROR(Status) )
        return FALSE; 

    if( gExFlashPart.FlashVenDevId != 0 )
    {
        return SwitchSpiFlashAddressMode( gExFlashPart.FlashVenDevId, Mode );
    }
    return FALSE;
}

/**
    This function get the current SPI flash addressing mode

    @retval THREE_BYTE_ADDR_MODE(0x3) or FOUR_BYTE_ADDR_MODE(0x4)
**/
UINT8
EFIAPI
CheckSpiFlashAddressMode()
{
    EFI_STATUS  Status; 

    Status = UpdateEarSpiFlashInfo();
    if( EFI_ERROR(Status) )
        return THREE_BYTE_ADDR_MODE; 

    if( gExFlashPart.FlashVenDevId != 0 )
    {
        return GetSpiFlashAddressMode( gExFlashPart.FlashVenDevId );
    }
    return THREE_BYTE_ADDR_MODE;
}
