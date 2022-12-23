//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************


/** @file CpuBoard.h
    This file declares types, functions, and constants for 
    OEM-related initialization to be done in CPU during DXE
    phase.
**/
#ifndef __CPU_BOARD_H__
#define __CPU_BOARD_H__

#include <EFI.h>
#include <CacheSubClass.h>
#include "Cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

// These structures/constants are used to initialize CACHE_DESCRIPTOR_INFO
// structures to describe each CPU's cache structures in InitializeCpu()
typedef enum 	{
    EAX	= 0,
    EBX	= 1,
    ECX	= 2,
    EDX	= 3,
} REGISTER_TYPE;

#pragma pack (push, 1)
typedef enum {
    CacheAssociativityOther        = 1,
    CacheAssociativityUnknown      = 2,
    CacheAssociativityDirectMapped = 3,
    CacheAssociativity2Way         = 4,
    CacheAssociativity3Way         = 5,
    CacheAssociativity4Way         = 6,
    CacheAssociativityFully        = 7,
    CacheAssociativity8Way         = 8,
    CacheAssociativity16Way        = 9,
    CacheAssociativity24Way        = 0x0A,
    CacheAssociativity32Way        = 0x0B,
    CacheAssociativity48Way        = 0x0C,
    CacheAssociativity64Way        = 0x0D
} AMD_CACHE_ASSOCIATIVITY_DATA;

typedef struct
{
    UINTN                           FieldValue;     // value read from register
    AMD_CACHE_ASSOCIATIVITY_DATA    SMBiosValue;    // SMBios encoded value
} ASSOC_MAP;

typedef struct
{
    ASSOC_MAP           *Map;
    UINTN               size;          // number of ASSOC_MAP entries
} ASSOC_ENCODING;

typedef struct
{
    UINT8               Level;          // EFI_CACHE_L1, EFI_CACHE_L2, 
                                        // or EFI_CACHE_L3
    EFI_CACHE_TYPE_DATA Type;           // Type of cache
    UINT32              FCpuID;         // CpuID function to retreive 
                                        // the cache's information
    REGISTER_TYPE       Register;       // The register that contains the 
                                        // cache information (EAX, EBX, ...)
    UINTN               SShift;         // amount of right-shift for size 
                                        // field
    UINT32              SMask;          // mask for size field
    UINTN               AShift;         // amount of right-shift for 
                                        // associativity field
    UINT32              AMask;          // mask for associativity field
    ASSOC_ENCODING      ATable;         // associativity encoding table
} CPU_CACHE_TABLE;
#pragma pack (pop)

typedef UINT32 REGISTER_TABLE[4];

EFI_STATUS BoardCpuInit();

/****** DO NOT WRITE BELOW THIS LINE *******/
#ifdef __cplusplus
}
#endif
#endif

//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************
