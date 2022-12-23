//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************

/** @file SecMain.h
    SEC definitions

**/


#ifndef _SECMAIN_H_
#define _SECMAIN_H_

#include <PiPei.h>
#include <Ppi/SecPlatformInformation.h>
#include <Library/BaseLib.h>

#include <Ppi/TemporaryRamSupport.h>

#include <Library/BaseMemoryLib.h>
#include <Library/DebugAgentLib.h>
#include <Library/UefiCpuLib.h>
#include <Library/DebugLib.h>
#include <Library/PeCoffGetEntryPointLib.h>
#include <Library/PeCoffExtraActionLib.h>
#include <Library/CpuExceptionHandlerLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/PeiServicesLib.h>

#define SEC_IDT_ENTRY_COUNT  34

typedef struct _SEC_IDT_TABLE {
  //
  // Reserved 8 bytes preceding IDT to store EFI_PEI_SERVICES**, since IDT base
  // address should be 8-byte alignment.
  // Note: For IA32, only the 4 bytes immediately preceding IDT is used to store
  // EFI_PEI_SERVICES**
  //
  UINT64            PeiService;
  UINT64            IdtTable[SEC_IDT_ENTRY_COUNT];
} SEC_IDT_TABLE;

#define PEI_ENTRY_POINTER_FIXED 0xFFFFFFE0

//-----------------------------------------------------------------------------
//      Extended CPUID Equates
//-----------------------------------------------------------------------------
#define AMD_EXT_CPUID_1             0x80000001  // Family Model Features information

//This is copied from AmdSoc.h
#define AMI_CPUID_STEPPING_MASK      0x0000000F
#define AMI_CPUID_BASE_MODEL_MASK    0x000000F0
#define AMI_CPUID_BASE_FAMILY_MASK   0x00000F00
#define AMI_CPUID_EXT_MODEL_MASK     0x000F0000
#define AMI_CPUID_EXT_FAMILY_MASK    0x0FF00000

#define AMI_RAW_FAMILY_ID_MASK (UINT32) (AMI_CPUID_EXT_FAMILY_MASK | AMI_CPUID_EXT_MODEL_MASK | AMI_CPUID_BASE_FAMILY_MASK)

#define AMI_F15_BR_RAW_ID   0x00660F00

VOID
EFIAPI
SecCPhase2 (
  IN    VOID    *Context
);

EFI_STATUS TemporaryRamMigration(
  IN CONST EFI_PEI_SERVICES   **PeiServices,
  IN EFI_PHYSICAL_ADDRESS     TemporaryMemoryBase,
  IN EFI_PHYSICAL_ADDRESS     PermanentMemoryBase,
  IN UINTN                    CopySize
);

VOID
EFIAPI
SecSwitchStack (
  UINT32   OldStack,
  UINT32   NewStack
  );

#endif

//**********************************************************************
//**********************************************************************
//**                                                                  **
//**        (C)Copyright 1985-2019, American Megatrends, Inc.         **
//**                                                                  **
//**                       All Rights Reserved.                       **
//**                                                                  **
//**      5555 Oakbrook Parkway, Suite 200, Norcross, GA 30093        **
//**                                                                  **
//**                       Phone: (770)-246-8600                      **
//**                                                                  **
//**********************************************************************
//**********************************************************************
