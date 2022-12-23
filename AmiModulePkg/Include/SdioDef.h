//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file SdioDef.h
    Header file for Smm and Non Smm interface

**/

#ifndef _AMI_SDIO_DEF_H_
#define _AMI_SDIO_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MICROSECOND                     10
#define MILLISECOND                     (1000 * MICROSECOND)
#define ONESECOND                       (1000 * MILLISECOND)

#define SDIO_DATA_EBDA_OFFSET 0x104

#define SDIO_API_DEVICE_DETECT              0
#define SDIO_API_DEVICE_CONFIGURE           1
#define SDIO_API_GET_MASS_DEVICE_DETAILS    2
#define SDIO_API_READ                       3
#define SDIO_API_WRITE                      4
#define SDIO_API_GET_DEVICE_GEOMETRY	    5
#define SDIO_API_RESET_DEVICE 	            6

//----------------------------------------------------------------------------
//      SDIO Mass Storage Related Data Structures and Equates
//----------------------------------------------------------------------------
#define SDIO_EMU_NONE            0
#define SDIO_EMU_FLOPPY_ONLY     1
#define SDIO_EMU_HDD_ONLY        2
#define SDIO_EMU_FORCED_FDD      3

// Values for Mass Storage Device type
//-------------------------------------
#define SDIO_MASS_DEV_HDD        1
#define SDIO_MASS_DEV_ARMD       2


// Error returned from API handler
#define     SDIO_SUCCESS                0x000
#define     SDIO_PARAMETER_ERROR        0x010
#define     SDIO_NOT_SUPPORTED          0x020
#define     SDIO_INVALID_FUNCTION       0x0F0
#define     SDIO_ERROR                  0x0FF

#define     SDIO_MANUFACTUREID_LENGTH   30

#define SDIO_RUNTIME_DATA_GUID \
        { 0x381a469f, 0x34f8, 0x4081, { 0xb2, 0xd5, 0xbb, 0x29, 0x8f, 0xb6, 0xa9, 0xf0 } }

#pragma pack(1)
/**
    This is a URP (SDIO Request Packet) structure for the BIOS
    API call Controller Info

**/

typedef struct {
    UINT32      TransferBufferAddress;
    UINT64      AdmaDescriptorAddress;
    UINT64      SdioBaseAddress;
    UINT8       PciBus;
    UINT8       PciDevice;
    UINT8       PciFunc;
    UINT8       Port;
    BOOLEAN     DeviceDetected;
    UINT8       DeviceAddress;
    UINT8       NumHeads;
    UINT8       LBANumHeads;
    UINT16      NumCylinders;
    UINT16      LBANumCyls;
    UINT8       NumSectors;
    UINT8       LBANumSectors;
    UINT32      MaxLBA;
    UINT16      BlockSize;
    UINT8       StorageType;
    UINT8       PNM[27];
    BOOLEAN     SdIODevice;
    UINT8       SdioAccessMode;
    UINT8       SdIOManufactureId[SDIO_MANUFACTUREID_LENGTH];
} SDIO_CONTROLLER_INFO;

/**
    This is a URP (SDIO Request Packet) structure for the BIOS
    API call Reset SDIO

**/

typedef struct {
    UINT8       DeviceAddress;
} RESET_SDIO;

/**
    This is a URP (SDIO Request Packet) structure for the BIOS
    API call Read 

**/

typedef struct {
    UINT8       DeviceAddress;
    UINT8       Port;
    UINT32      LBA;            // Starting LBA address
    UINT32      NumBlks;        // Number of blocks to read
    UINT32      BufferAddress;  // Far buffer pointer
} SDIO_READ_DATA;

/**
    This is a URP (SDIO Request Packet) structure for the BIOS
    API call Device Geometry 

**/

typedef struct {
    UINT8       DeviceAddress;
    UINT8       NumHeads;
    UINT16      NumCylinders;
    UINT8       NumSectors;
    UINT8       LBANumHeads;
    UINT16      LBANumCyls;
    UINT8       LBANumSectors;
    UINT16      BlockSize;
    UINT32      MaxLBA;
    UINT8       Int13FunctionNo;
} SDIO_DEVICE_GEO;

/**
    This is a union data type of all the API related data

**/

typedef union {
    RESET_SDIO              Reset;
    SDIO_CONTROLLER_INFO         ControllerInfo;
    SDIO_READ_DATA               Read;    
    SDIO_DEVICE_GEO              DeviceGeo;
} SDIO_API_DATA;

/**
    This structure is the URP structure

 Fields:   Name       Type        Description
      ------------------------------------------------------------
      bFuncNumber UINT8       Function number of the URP
      bSubFunc    UINT8       Sub-func number of the URP
      bRetValue   UINT8       Return value
      ApiData     API_DATA    Refer structure definition
**/

typedef struct {
    UINT8           bFuncNumber;
    UINT8           bSubFunc;
    UINT8           bRetValue;
    SDIO_API_DATA   ApiData;
} SDIO_STRUC;

#pragma pack()

// Defining a GUID for SDIO_PARAMETER_BASE_ADDRESS_GUID
#define SDIO_PARAMETER_BASE_ADDRESS_GUID \
{ 0x17d6d323, 0x43ce, 0x438a, { 0xbc, 0x95, 0x78, 0xa2, 0xde, 0x99, 0x19, 0xd7 } }

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif


