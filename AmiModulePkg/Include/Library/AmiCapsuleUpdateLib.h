//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/** @file
  Definition of the AmiCapsuleUpdateLib library class.
*/
#ifndef __AMI_CAPSULE_UPDATE_LIB__H__
#define __AMI_CAPSULE_UPDATE_LIB__H__

#include <Uefi.h>

/// The library class is used by the Recovery module to extract flashable image from the capsule.

/**
  Extracts actual flash update image from capsule

  @param Capsule Pointer to capsule
  @param CapsuleSize Capsule size
  @param Payload Pointer where to store pointer to Flash update image
  @param PayloadSize Pointer where to store Flash update image size

  @retval  EFI_SUCCESS  Returned flash update image is valid
  @retval  Other        Error occured during operation
*/
EFI_STATUS AmiPreprocessCapsule (
    IN EFI_CAPSULE_HEADER *Capsule,
    IN UINT32 CapsuleSize,
    OUT VOID **Payload,
    OUT UINT32 *PayloadSize
);

/**
  Checks if capsule contains system firmware image

  @param Capsule Pointer to capsule

  @retval  TRUE  Capsule contains main firmware update image
  @retval  FALSE Capsule doesn't contain main firmware update image
*/
BOOLEAN AmiIsFwUpdateCapsule (
    IN EFI_CAPSULE_HEADER *Capsule
);

/**
  Checks if capsule firmware image is passed via ESRT mechanism

  @param Capsule Pointer to capsule

  @retval  TRUE  Capsule is passed via ESRT mechanism
  @retval  FALSE Capsule isn't passed via ESRT mechanism
*/
BOOLEAN AmiIsEsrtUpdateCapsule (
    IN EFI_CAPSULE_HEADER *Capsule
);

/**
  Checks if capsule requires reset after processing
 
  @param Guid Pointer to capsule guid
 
  @retval TRUE - Capsule requires system reset after processing
  @retval FALSE - Capsule does not system reset
 */
BOOLEAN AmiIsResetAfterCapsuleGuid (
    IN EFI_GUID *Guid
);
#endif
