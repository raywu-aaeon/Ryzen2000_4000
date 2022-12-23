//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2019, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************


/** @file PeiInitializeMtrrLib.c
    This file is to get the MTRR hob to restore MTRR

**/
#include <PiPei.h>
#include <Register/Msr.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Token.h>

typedef struct {
    EFI_HOB_GUID_TYPE       EfiHobGuidType;
    UINT64                  VarMtrrBase[7];
    UINT64                  VarMtrrMask[7];
} MTRR_HOB;

extern  EFI_GUID    gAmiMTRRHobGuid;

#define MEM_DET_COMMON_MEM_ATTR     (EFI_RESOURCE_ATTRIBUTE_PRESENT | \
                                    EFI_RESOURCE_ATTRIBUTE_INITIALIZED | \
                                    EFI_RESOURCE_ATTRIBUTE_TESTED | \
                                    EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |\
                                    EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE | \
                                    EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE | \
                                    EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE)

/**
    Restore the MTRR which is saved in CreateMtrrHob of MemDetect.c.

        
    @retval NULL

**/
VOID
EFIAPI
InitializeMtrr(
  VOID
  )
{
    // Fam 17 CPU doesn't have AP at PEI phase.
    return;
}

