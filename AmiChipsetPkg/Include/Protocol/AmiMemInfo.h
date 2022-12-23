//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file AmiMemInfo.h
    The header file for AMI Memory Information

*/

#ifndef _AMI_MEMORY_INFO_
#define _AMI_MEMORY_INFO_

#ifdef __cplusplus
extern "C" {
#endif

#include <Token.h>
#include <Library/PcdLib.h>
#include <Protocol/SmbusHc.h>

#define AMI_MEMORY_INFO_GUID \
  {0xa8f960c6, 0x4cc3, 0x4417, 0x8a, 0xd9, 0x2a, 0x3b, 0x3f, 0x80, 0x27, 0xea}

extern EFI_GUID gAmiMemoryInfoGuid;

#define AMI_MEMORY_INFO_VARIABLE L"AmiMemoryInfo"

#pragma pack(push,1)

typedef enum {
    UnknownType,
    DDR1,
    DDR2,
    DDR3,
    DDR3L,
    DDR3U,
    LPDDR3,
    DDR4,
    LPDDR4,
    OtherType
} MEMORY_TYPE_INFO;

typedef struct {
    UINT32                    Size;                  // MB
    BOOLEAN                   DoubleSide;
    BOOLEAN                   Ecc;
    UINT8                     SpdAddr;
} MEMORY_SLOT_INFO;

typedef struct {
    MEMORY_TYPE_INFO          RamType;
    UINT32                    MaxCapacity;           // MB
    UINT32                    TotalMemory;           // MB
    UINT32                    Speed;                 // Mhz
    // DIMM_SLOT_NUM is defined in Nb.sdl of AmiChipsetModulePkg
    MEMORY_SLOT_INFO          Slot[DIMM_SLOT_NUM];
} AMI_MEMORY_ARRAY_INFO;

typedef struct {
    // MEMORY_ARRAY_NUM is defined in Nb.sdl of AmiChipsetModulePkg
    AMI_MEMORY_ARRAY_INFO     MemoryArray[MEMORY_ARRAY_NUM];
} AMI_MEMORY_INFO;

#pragma pack(pop)

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif

#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2018, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
