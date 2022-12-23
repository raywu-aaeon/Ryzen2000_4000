//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file AmdExtSpiFlash.h
    This file contains the structure and function prototypes needed
    for the AMD extend Flash library

**/

#ifndef _ExtSpiFlash_H_
#define _ExtSpiFlash_H_

//Winbond
#define WINBOND_W25Q256FV           0x1940EF
#define WINBOND_W25Q256JW           0x1960EF
#define WINBOND_W25Q256JW_2         0x1980EF
#define WINBOND_W25Q256JV           0x1970EF

// Giga Device
#define GD25R256D                   0x1940C8
#define GD25LR256E                  0x1967C8

// MXIC
#define MX25L25633F                 0x1920C2
#define MX25U25635F                 0x3925C2
#define MX77U25650F                 0x3975C2
#define MX77L25650F                 0x1975C2

// MICRON
#define MT25QL256ABA                0x19BA20
#define MT25QL256ABA_2              0x19BB20

// ISSI
#define IS25LP256E                  0x19609D
#define IS25WP256E                  0x19709D

// MXC
#define XM25QU256B                  0x197020
#define XM25RH256C                  0x194320

// Adesto


typedef 
EFI_STATUS 
(EFIAPI *EXT_SPI_FLASH_EAR_READ) (
    OUT UINT8       *SegmentIndex
);
typedef 
EFI_STATUS 
(EFIAPI *EXT_SPI_FLASH_EAR_CHANGE) (
    UINT8       SegmentIndex
);

typedef struct _EXT_SPI_FLASH_FUNC_INFO {
    UINT32                      SpiDeviceId;
    UINT8                       ReadEarOp;
    UINT8                       WriteEarOp;
    EXT_SPI_FLASH_EAR_READ      ExtSpiFlashEarRead;
    EXT_SPI_FLASH_EAR_CHANGE    ExtSpiFlashEarChange;
}EXT_SPI_FLASH_FUNC_INFO;

VOID
CommonSpiWriteStatus(
    IN UINT8                bWriteData,
    IN UINT8                bOpcodeIndex,
    IN UINT8                bIsDataPhase,
    IN UINT8                bPrefixOp,
    IN UINT32               dSectorAddress
);

UINT8 CommonSpiReadStatus (VOID);

EFI_STATUS UpdateEarSpiFlashInfo(VOID);

EFI_STATUS EFIAPI CommonExtSpiFlashEarRead (UINT8 *SegmentIndex);
EFI_STATUS EFIAPI IssiExtSpiFlashEarRead (UINT8 *SegmentIndex);

EFI_STATUS EFIAPI CommonExtSpiFlashEarChange (UINT8 SegmentIndex);
EFI_STATUS EFIAPI IssiExtSpiFlashEarChange (UINT8 SegmentIndex);

BOOLEAN EFIAPI ChangeSpiFlashAddressMode( IN  UINT8   Mode );
UINT8 EFIAPI CheckSpiFlashAddressMode();

#endif