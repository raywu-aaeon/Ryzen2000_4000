//**********************************************************************
//*                                                                    *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.  *
//*                                                                    *
//*      All rights reserved. Subject to AMI licensing agreement.      *
//*                                                                    *
//**********************************************************************

/** @file
  AmiFwCapsuleGuids.h is generated by AMISDL from AmiFwCapsuleGuidsTemplate.h
  This header file defines GUIDs of system FW Capsules supported by the platform.
  AMISDL replaces @@elink commands below with the content of the corresponding eLink.

  Do not include this header in your source file. It is a private header of the AmiCapsuleUpdateLib.
**/

#ifndef __AMI_FW_CAPSULE_GUID_LIST__H__
#define __AMI_FW_CAPSULE_GUID_LIST__H__

#include <Uefi.h>

static EFI_GUID AmiFwCapsuleGuidList[] = {
@elink(AmiFwCapsuleGuids, "   @child", ",%n", "")
};
static UINT32 AmiFwCapsuleGuidListSize = sizeof (AmiFwCapsuleGuidList) / sizeof (EFI_GUID);

static EFI_GUID AmiEsrtCapsuleGuidList[] = {
@elink(AmiEsrtCapsuleGuids, "   @child", ",%n", "")
};
static UINT32 AmiEsrtCapsuleGuidListSize = sizeof (AmiEsrtCapsuleGuidList) / sizeof (EFI_GUID);

static EFI_GUID AmiResetAfterCapsuleGuidList[] = {
@elink(AmiResetAfterCapsuleGuids, "   @child", ",%n", "")
};
static UINT32 AmiResetAfterCapsuleGuidListSize = sizeof (AmiResetAfterCapsuleGuidList) / sizeof (EFI_GUID);
#endif
