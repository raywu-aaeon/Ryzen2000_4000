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

/** @file MemDetect.h
    Memdetect definitions 

**/
#ifndef __MEMDETECT__H__
#define __MEMDETECT__H__
#ifdef __cplusplus
extern "C" {
#endif

//
// Include files
//

#include "Efi.h"
#include "Pei.h"
#include "Agesa.h"
#include "Library/AmdCalloutLib.h"


EFI_STATUS
EFIAPI 
PlatformDimmSpdRead (
  IN      EFI_PEI_SERVICES                    **PeiServices,  ///< Pointer to PeiServices
  IN struct _PEI_AMD_PLATFORM_DIMM_SPD_PPI    *This,          ///< Pointer to the PPI structure
  IN OUT  AGESA_READ_SPD_PARAMS               *SpdData        ///< SPD Data Buffer
  );

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
