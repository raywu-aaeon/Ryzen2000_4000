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

/** @file AmiShadowLib.h
  This file contains North Bridge chipset porting library shadow 
  functions and data structure definitions for both PEI & DXE stages.
  
*/

#ifndef __AMI_SHADOW_LIB_H__
#define __AMI_SHADOW_LIB_H__

#include <PiPei.h>
#include <Uefi.h>
#include "Token.h"
#include <Protocol/PciRootBridgeIo.h>


#ifdef __cplusplus
extern "C" {
#endif

#define REGION_DECODE_ROM   0                       //Read/Write ROM
#define REGION_LOCK     1                           //Read Only
#define REGION_UNLOCK   3                           //Read/Write Only
#define LEGACY_REGION_LOCK          0               // Read only Read to RAM, Write to ROM
#define LEGACY_REGION_BOOT_LOCK     1
#define LEGACY_REGION_UNLOCK        2               // Read/Write to RAM
#define LEGACY_REGION_DECODE_ROM    3               // Read/Write to ROM

//
// Shadow Attribute
//
#pragma pack (push, 1)
typedef enum {
  AmiShadowDisabled,   // Read/Write are both disabled
  AmiShadowReadOnly,   // Read Only
  AmiShadowWriteOnly,  // Write Only
  AmiShadowReadWrite   // Read/Write are both enabled
} SHADOW_ARRTIBUTE;

typedef struct
{
	UINT8 	Register;
	UINT8 	MaskShift;
	UINT32	StartAddress;
	UINT32	Length;
} PAM_STRUCT;
#pragma pack (pop)

//
// BIOS Range to shadow
//
typedef enum {
    C0000_16K,  // 0C0000-0C3FFF
    C4000_16K,  // 0C4000-0C7FFF
    C8000_16K,  // 0C8000-0CBFFF
    CC000_16K,  // 0CC000-0CFFFF
    D0000_16K,  // 0D0000-0D3FFF
    D4000_16K,  // 0D4000-0D7FFF
    D8000_16K,  // 0D8000-0DBFFF
    DC000_16K,  // 0DC000-0DFFFF
    E0000_16K,  // 0E0000-0E3FFF
    E4000_16K,  // 0E4000-0E7FFF
    E8000_16K,  // 0E8000-0EBFFF
    EC000_16K,  // 0EC000-0EFFFF
    F0000_64K   // 0F0000-0FFFFF
} SHADOW_BIOS_RANGE;

EFI_STATUS
NbProgramPamRegisters (
    IN EFI_BOOT_SERVICES    *gBS,
    IN EFI_RUNTIME_SERVICES *gRS,
    IN UINT32               StartAddress, 
    IN UINT32               Length,
    IN UINT8                Setting, 
    IN UINT32               *Granularity
);

EFI_STATUS NbPeiProgramPamRegisters(
    IN EFI_PEI_SERVICES **PeiServices,
    IN UINT32           StartAddress,
    IN UINT32           Length,
    IN UINT8            Setting,
    IN UINT32           *Granularity OPTIONAL
);

VOID NbRuntimeShadowRamWrite(
    IN BOOLEAN Enable
);

EFI_STATUS
NbRuntimeShadowRamWriteExt (
    IN SHADOW_ARRTIBUTE   Attribute,
    IN SHADOW_BIOS_RANGE  Range
);

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
