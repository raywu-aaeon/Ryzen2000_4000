//*************************************************************************
//*************************************************************************
//**                                                                     **
//**        (C)Copyright 1985-2019 American Megatrends, Inc.            **
//**                                                                     **
//**                       All Rights Reserved.                          **
//**                                                                     **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093           **
//**                                                                     **
//**                       Phone: (770)-246-8600                         **
//**                                                                     **
//*************************************************************************
//*************************************************************************

/** @file CpuBoard.c
    Board specific functions called from DXE.
**/

#include <Efi.h>
#include <CpuBoard.h>
#include <AmiLib.h>
#include <AmiDxeLib.h>
#include "Nb.h"

extern   UINT32 CpuReadPCI32(IN UINT32);

#define  PCI_ADDRESS(bus, dev, func, reg) \
            ((UINT64) ( (((UINTN)bus) << 16) + (((UINTN)dev) << 11) + \
            (((UINTN)func) << 8) + ((UINTN)reg) )) & 0x00000000ffffffff

// L1 instruction and data cache associativity encoding from the
// return value of CPUID to the SMBios specification's byte value.
ASSOC_MAP   L1AMap[] = 
    { 
     /* CPUID value, SMBios associativity encoding     */
      { 1,           CacheAssociativityDirectMapped },
      { 2,           CacheAssociativity2Way,        },
      { 3,           CacheAssociativity3Way,        },
      { 4,           CacheAssociativity4Way,        },
      { 8,           CacheAssociativity8Way,        },
      { 16,          CacheAssociativity16Way,       },
      { 0xff,        CacheAssociativityFully,       }
    };
#define L1ASIZE sizeof(L1AMap) / sizeof(ASSOC_MAP)

// L2 data cache associativity encoding from the
// return value of CPUID to the SMBios specification's byte value.
ASSOC_MAP   L2AMap[] = 
    { 
     /* CPUID value, SMBios associativity encoding     */
      { 0,           CacheAssociativityUnknown      },
      { 1,           CacheAssociativityDirectMapped },
      { 2,           CacheAssociativity2Way         },
      { 4,           CacheAssociativity4Way         },
      { 6,           CacheAssociativity8Way         },
      { 8,           CacheAssociativity16Way        },
      { 0xf,         CacheAssociativityFully        }
    };
#define L2ASIZE sizeof(L2AMap) / sizeof(ASSOC_MAP)

// L3 data cache associativity encoding from the
// return value of CPUID to the SMBios specification's byte value.
ASSOC_MAP   L3AMap[] = 
    { 
     /* CPUID value, SMBios associativity encoding     */
        { 0,        CacheAssociativityUnknown        },
        { 1,        CacheAssociativityDirectMapped   },
        { 2,        CacheAssociativity2Way           },
        { 4,        CacheAssociativity4Way           },
        { 6,        CacheAssociativity8Way           },
        { 8,        CacheAssociativity16Way          },
        { 0xa,      CacheAssociativity32Way          },
        { 0xb,      CacheAssociativity48Way          },
        { 0xc,      CacheAssociativity64Way          },
        { 0xd,      CacheAssociativityUnknown        }, // 96 way
        { 0xe,      CacheAssociativityUnknown        }, // 128 way
        { 0xf,      CacheAssociativityFully          }
    };
#define L3ASIZE sizeof(L3AMap) / sizeof(ASSOC_MAP)

// Describe how to retrieve cache information for each 
// instruction and data cache for the CPU.
CPU_CACHE_TABLE         CacheTable[] =
    {{ EFI_CACHE_L1, EfiCacheTypeInstruction, AMD_EXT_CPUID_5,
       EDX, 24, 0xFF, 16, 0xFF, {L1AMap, L1ASIZE} },
     { EFI_CACHE_L1, EfiCacheTypeData, AMD_EXT_CPUID_5,
       ECX, 24, 0xFF, 16, 0xFF, {L1AMap, L1ASIZE} },
     { EFI_CACHE_L2, EfiCacheTypeData, AMD_EXT_CPUID_6,
       ECX, 16, 0xFFFF, 12, 0xF, {L2AMap, L2ASIZE} },
     { EFI_CACHE_L3, EfiCacheTypeData, AMD_EXT_CPUID_6,
	   EDX, 18, 0x3FFF, 12, 0xF, {L3AMap, L3ASIZE}}};
UINT8 CacheSize = sizeof(CacheTable) / sizeof(CPU_CACHE_TABLE);

/**
    Read the PCI Register

    @param Address (UINT32) ( (((UINT32)bus) << 24) + (((UINT32)dev) << 19) + (((UINT32)func) << 16) + ((UINT32)reg) )

    @retval UINT32 return value from the PCI Register.

**/
UINT32 CpuReadPCI32(
    IN UINT32 Address
)
{
    UINT32 Value32;
    UINT32 AddrCf8 = (1 << 31) + (Address & 0x0FFFF00) + (Address & 0xFC);

    IoWrite32(0xCF8, AddrCf8);
    Value32 = IoRead32(0xCFC);
    return Value32;
}

/**
    Board specfic CPU changes. This function will only execute
    on the BSP.

    @param VOID

    @retval EFI_STATUS return the EFI status

**/

EFI_STATUS BoardCpuInit(VOID)
{
    EFI_STATUS  Status = EFI_SUCCESS;

    return Status;
}

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
