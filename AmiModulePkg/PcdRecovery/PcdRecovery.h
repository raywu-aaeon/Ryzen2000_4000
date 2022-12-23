//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************
/** @file PcdRecovery.h
    PcdRecovery Definitions

**/
//**********************************************************************
#ifndef __PCDRECOVERY__H__
#define __PCDRECOVERY__H__

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Uefi/UefiSpec.h>
#include <Uefi/UefiMultiPhase.h>
#include <Pi/PiMultiPhase.h>

#ifndef FID_FFS_FILE_NAME_GUID
#define FID_FFS_FILE_NAME_GUID \
    { 0x3fd1d3a2, 0x99f7, 0x420b, {0xbc, 0x69, 0x8b, 0xb1, 0xd4, 0x92, 0xa3, 0x32 }}
#endif

#ifndef FID_FFS_FILE_SECTION_GUID
#define FID_FFS_FILE_SECTION_GUID \
    { 0x2EBE0275, 0x6458, 0x4AF9, {0x91, 0xED, 0xD3, 0xF4, 0xED, 0xB1, 0x00, 0xAA }}
#endif

#define AMI_PCD_RECOVERY_HOB_GUID \
    { 0x609F29FE, 0x8FA7, 0x4C77, {0xA6, 0xF8, 0x18, 0x6F, 0x7E, 0x74, 0xE8, 0x03}}

static EFI_GUID gAmiPcdRecoveryHobGuid = AMI_PCD_RECOVERY_HOB_GUID;

#pragma pack(push)
#pragma pack(1)

typedef struct {
    EFI_HOB_GUID_TYPE    EfiHobGuidType;
    FW_VERSION           FwVersionData;
    UINT8                IsRecovery;
    UINT32               SkuId;
} AMI_PCD_RECOVERY_HOB;

#pragma pack(pop)


#endif
