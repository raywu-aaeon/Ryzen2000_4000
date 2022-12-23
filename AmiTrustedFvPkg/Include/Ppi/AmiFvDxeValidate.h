//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  Defines PPI that is used to verify integrity of all FW regions containing DXE code.
**/
#ifndef __AMI_FV_DXE_VALIDATE_PPI__H__
#define __AMI_FV_DXE_VALIDATE_PPI__H__

#include <Library/AmiRomLayoutLib.h>
#include <Ppi/AmiFvDigest.h>

//#ifndef AMI_ROM_AREA_MEASURED
//  AmiModulePkg_48 (Core 5.15) removed "TCG" from "AMI_ROM_AREA_TCG_MEASURED"
//#define AMI_ROM_AREA_MEASURED             0x00008000
//#endif

typedef struct _AMI_PUBLISH_FV_DXE_PPI {
   AMI_ROM_AREA     Area;
} AMI_PUBLISH_FV_DXE_PPI;

//
// TDXE - Trusted Dxe FV
//
#define AMI_FV_DXE_VALIDATE_PPI_GUID \
  { \
    0x3771aec7, 0xeac0, 0x4caa, {0xaf, 0x73, 0x4b, 0xf4, 0xc7, 0x6a, 0xd2, 0x29 } \
  }

typedef struct _AMI_FV_DXE_VALIDATE_PPI AMI_FV_DXE_VALIDATE_PPI;

typedef 
EFI_STATUS
(EFIAPI *AMI_PEI_FVDXE_VALIDATE) (
    IN AMI_FV_DXE_VALIDATE_PPI  *This,
    IN CONST EFI_PEI_SERVICES  **PeiServices,
    IN OUT AMI_ROM_AREA *Area OPTIONAL
);

#pragma pack (4)
struct _AMI_FV_DXE_VALIDATE_PPI {
  AMI_PEI_FVDXE_VALIDATE  FvDxeValidate;
  // for internal use
  VOID                    *AmiSigPpi;
  BOOLEAN                 bFvDxeProcessed;
  BOOLEAN                 bFvDxeSigStatus;
  BOOLEAN                 bFvDxeMfstStatus;
  BOOLEAN                 bFvDxeFvPeiMemValid;
};
#pragma pack()

#endif
