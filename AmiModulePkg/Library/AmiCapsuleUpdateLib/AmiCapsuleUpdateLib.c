//***********************************************************************
//*                                                                     *
//*   Copyright (c) 1985-2020, American Megatrends International LLC.   *
//*                                                                     *
//*      All rights reserved. Subject to AMI licensing agreement.       *
//*                                                                     *
//***********************************************************************

/**
 * @file AmiCapsuleUpdateLib.c
 * @brief Implementation of AmiCapsuleUpdate default library
 */

#include <AmiFwCapsuleGuids.h>
#include <Library/BaseMemoryLib.h>
#include <Library/AmiCapsuleUpdateLib.h>

/**
 * @brief Returns payload from capsule
 *
 * @param Capsule Pointer to capsule
 * @param CapsuleSize Capsule size
 * @param Payload Pointer where to return pointer to payload
 * @param PayloadSize Pointer where to return payload size
 *
 * @return Status of operation
 */
EFI_STATUS AmiPreprocessCapsule (
    IN EFI_CAPSULE_HEADER *Capsule,
    IN UINT32 CapsuleSize,
    OUT VOID **Payload OPTIONAL,
    OUT UINT32 *PayloadSize OPTIONAL
    )
{
    UINT8 *p = (UINT8 *)Capsule;
    UINT32 sz = CapsuleSize;

    if (AmiIsEsrtUpdateCapsule(Capsule)) {
        p = p + Capsule->HeaderSize;
        sz = CapsuleSize - Capsule->HeaderSize;
    }

    if (Payload)
        *Payload = p;
    if (PayloadSize)
        *PayloadSize = sz;

    return EFI_SUCCESS;
}

/**
 * @brief Checks if capsule is main firmware update capsule
 *
 * @param Capsule Pointer to capsule
 *
 * @retval TRUE - Capsule is the main firmware update capsule
 * @retval FALSE - Capsule is not the main firmware update capsule
 */
BOOLEAN AmiIsFwUpdateCapsule (
    IN EFI_CAPSULE_HEADER *Capsule
    )
{
    UINT32 i;
    for (i = 0; i < AmiFwCapsuleGuidListSize; i++) {
        if (CompareGuid (&Capsule->CapsuleGuid, AmiFwCapsuleGuidList + i))
            return TRUE;
    }
    return FALSE;
}

/**
 * @brief Checks if capsule is ESRT firmware update capsule
 *
 * @param Capsule Pointer to capsule
 *
 * @retval TRUE - Capsule is the ESRT firmware update capsule
 * @retval FALSE - Capsule is not the ESRT firmware update capsule
 */
BOOLEAN AmiIsEsrtUpdateCapsule (
    IN EFI_CAPSULE_HEADER *Capsule
    )
{
    UINT32 i;
    for (i = 0; i < AmiEsrtCapsuleGuidListSize; i++) {
        if (CompareGuid (&Capsule->CapsuleGuid, AmiEsrtCapsuleGuidList + i))
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief Checks if capsule requires reset after processing
 *
 * @param Guid Pointer to capsule guid
 *
 * @retval TRUE - Capsule requires system reset after processing
 * @retval FALSE - Capsule does not system reset
 */
BOOLEAN AmiIsResetAfterCapsuleGuid (
    IN EFI_GUID *Guid
    )
{
    UINT32 i;
    for (i = 0; i < AmiResetAfterCapsuleGuidListSize; i++) {
        if (CompareGuid (Guid, AmiResetAfterCapsuleGuidList + i))
        return TRUE;
    }
    return FALSE;
}
