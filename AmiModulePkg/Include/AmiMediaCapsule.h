//**********************************************************************
//*                                                                    *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.  *
//*                                                                    *
//*      All rights reserved. Subject to AMI licensing agreement.      *
//*                                                                    *
//**********************************************************************

/** @file
  @brief AMI Media Capsule Variable definition.

  The file contains definition of the media capsule variable
**/

#ifndef __AMI_MEDIA_CAPSULE_VARIABLE__H__
#define __AMI_MEDIA_CAPSULE_VARIABLE__H__

static CHAR16 AmiMediaCapsuleVariableName[] = L"AmiMediaCapsuleVariableName";

#include <Protocol/DevicePath.h>

typedef struct {
    HARDDRIVE_DEVICE_PATH Storage;
    CHAR16 ImageName[256];
    UINT32 ImageSize;
} AMI_MEDIA_CAPSULE_VARIABLE;

#endif
