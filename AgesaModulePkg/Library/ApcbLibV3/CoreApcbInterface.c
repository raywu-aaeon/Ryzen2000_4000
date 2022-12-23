/* $NoKeywords:$ */
/**
 * @file
 *
 * core APCB interface
 *
 * Contains core interface to manipulate APCB V3
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  Lib
 * @e \$Revision: 309090 $   @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
 *
 */
/*
 ******************************************************************************
 *
 * Copyright 2008 - 2019 ADVANCED MICRO DEVICES, INC.  All Rights Reserved.
 *
 * AMD is granting you permission to use this software and documentation (if
 * any) (collectively, the "Materials") pursuant to the terms and conditions of
 * the Software License Agreement included with the Materials.  If you do not
 * have a copy of the Software License Agreement, contact your AMD
 * representative for a copy.
 *
 * You agree that you will not reverse engineer or decompile the Materials, in
 * whole or in part, except as allowed by applicable law.
 *
 * WARRANTY DISCLAIMER:  THE MATERIALS ARE PROVIDED "AS IS" WITHOUT WARRANTY OF
 * ANY KIND.  AMD DISCLAIMS ALL WARRANTIES, EXPRESS, IMPLIED, OR STATUTORY,
 * INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE, NON-INFRINGEMENT, THAT THE
 * MATERIALS WILL RUN UNINTERRUPTED OR ERROR-FREE OR WARRANTIES ARISING FROM
 * CUSTOM OF TRADE OR COURSE OF USAGE.  THE ENTIRE RISK ASSOCIATED WITH THE USE
 * OF THE MATERIAL IS ASSUMED BY YOU.  Some jurisdictions do not allow the
 * exclusion of implied warranties, so the above exclusion may not apply to
 * You.
 *
 * LIMITATION OF LIABILITY AND INDEMNIFICATION:  AMD AND ITS LICENSORS WILL
 * NOT, UNDER ANY CIRCUMSTANCES BE LIABLE TO YOU FOR ANY PUNITIVE, DIRECT,
 * INCIDENTAL, INDIRECT, SPECIAL OR CONSEQUENTIAL DAMAGES ARISING FROM USE OF
 * THE MATERIALS OR THIS AGREEMENT EVEN IF AMD AND ITS LICENSORS HAVE BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.  In no event shall AMD's total
 * liability to You for all damages, losses, and causes of action (whether in
 * contract, tort (including negligence) or otherwise) exceed the amount of
 * $100 USD. You agree to defend, indemnify and hold harmless AMD and its
 * licensors, and any of their directors, officers, employees, affiliates or
 * agents from and against any and all loss, damage, liability and other
 * expenses (including reasonable attorneys' fees), resulting from Your use of
 * the Materials or violation of the terms and conditions of this Agreement.
 *
 * U.S. GOVERNMENT RESTRICTED RIGHTS:  The Materials are provided with
 * "RESTRICTED RIGHTS." Use, duplication, or disclosure by the Government is
 * subject to the restrictions as set forth in FAR 52.227-14 and
 * DFAR252.227-7013, et seq., or its successor.  Use of the Materials by the
 * Government constitutes acknowledgment of AMD's proprietary rights in them.
 *
 * EXPORT RESTRICTIONS: The Materials may be subject to export restrictions as
 * stated in the Software License Agreement.
 *******************************************************************************
 */

/*****************************************************************************
 *
 * This software package can be used to enable the Overclocking of certain
 * AMD processors and its use is subject to the terms and conditions of the
 * AMD Overclocking Waiver. Enabling overclocking through use of the low-level
 * routines included in this package and operating an AMD processor outside of
 * the applicable AMD product specifications will void any AMD warranty and can
 * result in damage to the processor or the system into which the processor has
 * been integrated. The user of this software assumes, and AMD disclaims, all
 * risk, liability, costs and damages relating to or arising from the overclocking
 * of AMD processors.
 *
 ******************************************************************************
 */

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include "Porting.h"
#include "Addendum/Apcb/Inc/SSP/APCB.h"
#include "CoreApcbInterface.h"
#include "CalloutLib.h"

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */


/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                          G L O B A L        V A L U E S
 *----------------------------------------------------------------------------------------
 */

/*---------------------------------------------------------------------------------------*/
/**
 *      This function retrieves the APCB structure/data versions
 *
 * @param[in]         apcbBuf              - Pointer to the APCB binary
 * @param[out]        StructVersion        - APCB Struct version
 * @param[out]        DataVersion          - APCB Data version
 *
 * @retval            CORE_APCB_OK
 *                    CORE_APCB_ERR_INVALID
 *
 */
CORE_APCB_RET_CODE
coreApcbGetVersion (
  IN         UINT8        *apcbBuf,
      OUT    UINT16       *StructVersion,
      OUT    UINT16       *DataVersion
  )
{
  APCB_V3_HEADER        *apcbHeader;

  customPrint ("\t[CORE APCB INFO] coreApcbGetVersion Entry\n");

  apcbHeader        = (APCB_V3_HEADER *)apcbBuf;

  if (APCB_SIGNATURE != apcbHeader->Signature) {
    customPrint ("\t[CORE APCB ERR] Invalid APCB data\n");
    return CORE_APCB_ERR_INVALID;
  }

  *StructVersion        = apcbHeader->StructVersion;
  *DataVersion          = apcbHeader->DataVersion;

  customPrint ("\t[CORE APCB INFO] APCB Struct Version = %04X\n", *StructVersion);
  customPrint ("\t[CORE APCB INFO] APCB Data Version = %04X\n", *DataVersion);

  return CORE_APCB_OK;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function retrieves a boolean APCB token
 *
 * @param[in]         apcbBuf         - Pointer to the APCB binary
 * @param[in]         priorityMask    - Priority Mask
 * @param[in]         boardMask       - Board Mask
 * @param[in]         typeInstance    - Type Instance
 * @param[in]         apcbToken       - APCB token ID
 * @param[out]        bValue          - APCB token value
 *
 * @retval            CORE_APCB_OK
 *                    CORE_APCB_ERR_TOKEN_NOT_FOUND
 *
 */
CORE_APCB_RET_CODE
coreApcbGetBool (
  IN         UINT8        *apcbBuf,
  IN         UINT8        priorityMask,
  IN         UINT16       boardMask,
  IN         UINT8        typeInstance,
  IN         UINT32       apcbToken,
      OUT    BOOLEAN      *bValue
  )
{
  UINT8                 *dataBuf;
  UINT32                dataSize;
  APCB_TOKEN_PAIR       *tempPair;

  customPrint ("\t[CORE APCB INFO] coreApcbGetBool Entry\n");

  if (CORE_APCB_OK == coreApcbGetType (apcbBuf, APCB_GROUP_COMMON, APCB_TYPE_TOKEN_BOOLEAN, priorityMask, boardMask, typeInstance, &dataBuf, &dataSize)) {
    for (tempPair = (APCB_TOKEN_PAIR *)dataBuf; (UINT8 *)tempPair < &dataBuf[dataSize]; tempPair ++) {
      if (tempPair->token == apcbToken) {
        *bValue = tempPair->value.bValue;
        customPrint ("\t[CORE APCB INFO] APCB token found: [%08X] = %08X\n", apcbToken, *bValue);
        return CORE_APCB_OK;
      }
    }
  }

  customPrint ("\t[CORE APCB ERR] APCB token not found\n");
  return CORE_APCB_ERR_TOKEN_NOT_FOUND;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function sets a boolean APCB token
 *
 * @param[in]         apcbBuf         - Pointer to the APCB binary
 * @param[in]         priorityMask    - Priority Mask
 * @param[in]         boardMask       - Board Mask
 * @param[in]         typeInstance    - Type Instance
 * @param[in]         sizeApcbBuf     - Size of the input APCB buffer. The buffer has to be
 *                                      big enough for a new token/value pair to be added.
 * @param[in]         apcbToken       - APCB token ID
 * @param[in]         bValue          - APCB token value
 *
 * @retval            CORE_APCB_OK
 *                    CORE_APCB_ERR_SPACE_NOT_ENOUGH
 *                    CORE_APCB_ERR_TYPE_NOT_FOUND
 *
 */
CORE_APCB_RET_CODE
coreApcbSetBool (
  IN  OUT     UINT8       *apcbBuf,
  IN          UINT32      sizeApcbBuf,
  IN          UINT8       priorityMask,
  IN          UINT16      boardMask,
  IN          UINT8       typeInstance,
  IN          UINT32      apcbToken,
  IN          BOOLEAN     bValue
  )
{
  UINT8                 *dataBuf;
  UINT32                dataSize;
  APCB_TOKEN_PAIR       *tempPair;
  APCB_V3_HEADER        *apcbHeader;
  APCB_GROUP_HEADER     *apcbGroupHeader;
  APCB_V3_TYPE_HEADER   *apcbTypeHeader;
  UINT8                 *apcbTempBuf;
  APCB_TOKEN_PAIR       *apcbInsertPair;
  UINT8                 *apcbEnding;
  UINT8                 *apcbGroupEnding;
  UINT32                *ApcbTail;
  UINT32                ApcbTailSizeInDword;
  UINT32                i;

  customPrint ("\t[CORE APCB INFO] coreApcbSetBool Entry\n");

  apcbTempBuf       = apcbBuf;
  apcbHeader        = (APCB_V3_HEADER *)apcbBuf;
  apcbEnding        = &apcbTempBuf[apcbHeader->SizeOfApcb];
  apcbGroupHeader   = (APCB_GROUP_HEADER *)&apcbHeader[1];

  if (APCB_SIGNATURE != apcbHeader->Signature) {
    customPrint ("\t[CORE APCB ERR] Invalid APCB data\n");
    return CORE_APCB_ERR_INVALID;
  }

  while ((UINT8 *)apcbGroupHeader < apcbEnding) {
    apcbTempBuf       = (UINT8 *)apcbGroupHeader;
    apcbGroupEnding   = &apcbTempBuf[apcbGroupHeader->SizeOfGroup];
    apcbTypeHeader    = (APCB_V3_TYPE_HEADER *)&apcbGroupHeader[1];
    while ((UINT8 *)apcbTypeHeader < apcbGroupEnding) {
      if (APCB_GROUP_COMMON == apcbTypeHeader->GroupId &&
          APCB_TYPE_TOKEN_BOOLEAN == apcbTypeHeader->TypeId &&
          typeInstance == apcbTypeHeader->InstanceId) {
        dataBuf          = (UINT8 *)&apcbTypeHeader[1];
        apcbInsertPair   = (APCB_TOKEN_PAIR *)dataBuf;
        dataSize         = apcbTypeHeader->SizeOfType - sizeof (APCB_V3_TYPE_HEADER);
        for (tempPair = (APCB_TOKEN_PAIR *)dataBuf; (UINT8 *)tempPair < &dataBuf[dataSize]; tempPair ++) {
          if (tempPair->token == apcbToken) {
            tempPair->value.bValue = bValue;
            customPrint ("\t[CORE APCB INFO] APCB token set: [%08X] = %08X\n", apcbToken, bValue);
            return CORE_APCB_OK;
          } else if (tempPair->token < apcbToken) {
            apcbInsertPair = &tempPair[1];
          }
        }

        if (sizeApcbBuf < apcbHeader->SizeOfApcb + sizeof (APCB_TOKEN_PAIR)) {
          customPrint ("\t[CORE APCB ERR] Not enough space to add a token\n");
          return CORE_APCB_ERR_SPACE_NOT_ENOUGH;
        }

        ApcbTailSizeInDword     = ((UINT32) (UINTN) (apcbEnding - (UINT8 *)apcbInsertPair)) / sizeof (UINT32);
        ApcbTail                = (UINT32 *)apcbInsertPair;
        for (i = 0; i < ApcbTailSizeInDword; i ++) {
          ApcbTail[ApcbTailSizeInDword - i + 1] = ApcbTail[ApcbTailSizeInDword - i - 1];
        }
        apcbInsertPair->token           = apcbToken;
        apcbInsertPair->value.bValue    = bValue;
        apcbTypeHeader->SizeOfType      += sizeof (APCB_TOKEN_PAIR);
        apcbGroupHeader->SizeOfGroup    += sizeof (APCB_TOKEN_PAIR);
        apcbHeader->SizeOfApcb += sizeof (APCB_TOKEN_PAIR);

        customPrint ("\t[CORE APCB INFO] APCB token appended: [%08X] = %08X\n", apcbToken, bValue);
        return CORE_APCB_OK;
      } else {
        apcbTempBuf       = (UINT8 *)apcbTypeHeader;
        apcbTypeHeader    = (APCB_V3_TYPE_HEADER *)&apcbTempBuf[apcbTypeHeader->SizeOfType];
      }
    }
    apcbGroupHeader = (APCB_GROUP_HEADER *)apcbTypeHeader;
  }

  customPrint ("\t[CORE APCB ERR] APCB type not found\n");
  return CORE_APCB_ERR_TYPE_NOT_FOUND;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function retrieves a UINT8 APCB token
 *
 * @param[in]         apcbBuf         - Pointer to the APCB binary
 * @param[in]         priorityMask    - Priority Mask
 * @param[in]         boardMask       - Board Mask
 * @param[in]         typeInstance    - Type Instance
 * @param[in]         apcbToken       - APCB token ID
 * @param[out]        Value8          - APCB token value
 *
 * @retval            CORE_APCB_OK
 *                    CORE_APCB_ERR_TOKEN_NOT_FOUND
 *
 */
CORE_APCB_RET_CODE
coreApcbGet8 (
  IN         UINT8        *apcbBuf,
  IN         UINT8        priorityMask,
  IN         UINT16       boardMask,
  IN         UINT8        typeInstance,
  IN         UINT32       apcbToken,
      OUT    UINT8        *value8
  )
{
  UINT8                 *dataBuf;
  UINT32                dataSize;
  APCB_TOKEN_PAIR       *tempPair;

  customPrint ("\t[CORE APCB INFO] coreApcbGet8 Entry\n");

  if (CORE_APCB_OK == coreApcbGetType (apcbBuf, APCB_GROUP_COMMON, APCB_TYPE_TOKEN_1BYTE, priorityMask, boardMask, typeInstance, &dataBuf, &dataSize)) {
    for (tempPair = (APCB_TOKEN_PAIR *)dataBuf; (UINT8 *)tempPair < &dataBuf[dataSize]; tempPair ++) {
      if (tempPair->token == apcbToken) {
        *value8 = tempPair->value.value8;
        customPrint ("\t[CORE APCB INFO] APCB token found: [%08X] = %08X\n", apcbToken, *value8);
        return CORE_APCB_OK;
      }
    }
  }

  customPrint ("\t[CORE APCB ERR] APCB token not found\n");
  return CORE_APCB_ERR_TOKEN_NOT_FOUND;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function sets a UINT8 APCB token
 *
 * @param[in]         apcbBuf         - Pointer to the APCB binary
 * @param[in]         priorityMask    - Priority Mask
 * @param[in]         boardMask       - Board Mask
 * @param[in]         typeInstance    - Type Instance
 * @param[in]         sizeApcbBuf     - Size of the input APCB buffer. The buffer has to be
 *                                      big enough for a new token/value pair to be added.
 * @param[in]         apcbToken       - APCB token ID
 * @param[in]         value8          - APCB token value
 *
 * @retval            CORE_APCB_OK
 *                    CORE_APCB_ERR_SPACE_NOT_ENOUGH
 *                    CORE_APCB_ERR_TYPE_NOT_FOUND
 *
 */
CORE_APCB_RET_CODE
coreApcbSet8 (
  IN  OUT    UINT8        *apcbBuf,
  IN  OUT    UINT32       sizeApcbBuf,
  IN         UINT8        priorityMask,
  IN         UINT16       boardMask,
  IN         UINT8        typeInstance,
  IN         UINT32       apcbToken,
  IN         UINT8        value8
  )
{
  UINT8                 *dataBuf;
  UINT32                dataSize;
  APCB_TOKEN_PAIR       *tempPair;
  APCB_V3_HEADER        *apcbHeader;
  APCB_GROUP_HEADER     *apcbGroupHeader;
  APCB_V3_TYPE_HEADER   *apcbTypeHeader;
  UINT8                 *apcbTempBuf;
  APCB_TOKEN_PAIR       *apcbInsertPair;
  UINT8                 *apcbEnding;
  UINT8                 *apcbGroupEnding;
  UINT32                *ApcbTail;
  UINT32                ApcbTailSizeInDword;
  UINT32                i;

  customPrint ("\t[CORE APCB INFO] coreApcbSet8 Entry\n");

  apcbTempBuf       = apcbBuf;
  apcbHeader        = (APCB_V3_HEADER *)apcbBuf;
  apcbEnding        = &apcbTempBuf[apcbHeader->SizeOfApcb];
  apcbGroupHeader   = (APCB_GROUP_HEADER *)&apcbHeader[1];

  if (APCB_SIGNATURE != apcbHeader->Signature) {
    customPrint ("\t[CORE APCB ERR] Invalid APCB data\n");
    return CORE_APCB_ERR_INVALID;
  }

  while ((UINT8 *)apcbGroupHeader < apcbEnding) {
    apcbTempBuf       = (UINT8 *)apcbGroupHeader;
    apcbGroupEnding   = &apcbTempBuf[apcbGroupHeader->SizeOfGroup];
    apcbTypeHeader    = (APCB_V3_TYPE_HEADER *)&apcbGroupHeader[1];
    while ((UINT8 *)apcbTypeHeader < apcbGroupEnding) {
      if (APCB_GROUP_COMMON == apcbTypeHeader->GroupId &&
          APCB_TYPE_TOKEN_1BYTE == apcbTypeHeader->TypeId &&
          typeInstance == apcbTypeHeader->InstanceId) {
        dataBuf          = (UINT8 *)&apcbTypeHeader[1];
        apcbInsertPair   = (APCB_TOKEN_PAIR *)dataBuf;
        dataSize         = apcbTypeHeader->SizeOfType - sizeof (APCB_V3_TYPE_HEADER);
        for (tempPair = (APCB_TOKEN_PAIR *)dataBuf; (UINT8 *)tempPair < &dataBuf[dataSize]; tempPair ++) {
          if (tempPair->token == apcbToken) {
            tempPair->value.value8 = value8;
            customPrint ("\t[CORE APCB INFO] APCB token set: [%08X] = %08X\n", apcbToken, value8);
            return CORE_APCB_OK;
          } else if (tempPair->token < apcbToken) {
            apcbInsertPair = &tempPair[1];
          }
        }

        if (sizeApcbBuf < apcbHeader->SizeOfApcb + sizeof (APCB_TOKEN_PAIR)) {
          customPrint ("\t[CORE APCB ERR] Not enough space to add a token\n");
          return CORE_APCB_ERR_SPACE_NOT_ENOUGH;
        }

        ApcbTailSizeInDword     = ((UINT32) (UINTN) (apcbEnding - (UINT8 *)apcbInsertPair)) / sizeof (UINT32);
        ApcbTail                = (UINT32 *)apcbInsertPair;
        for (i = 0; i < ApcbTailSizeInDword; i ++) {
          ApcbTail[ApcbTailSizeInDword - i + 1] = ApcbTail[ApcbTailSizeInDword - i - 1];
        }
        apcbInsertPair->token           = apcbToken;
        apcbInsertPair->value.value8    = value8;
        apcbTypeHeader->SizeOfType      += sizeof (APCB_TOKEN_PAIR);
        apcbGroupHeader->SizeOfGroup    += sizeof (APCB_TOKEN_PAIR);
        apcbHeader->SizeOfApcb += sizeof (APCB_TOKEN_PAIR);

        customPrint ("\t[CORE APCB INFO] APCB token appended: [%08X] = %08X\n", apcbToken, value8);
        return CORE_APCB_OK;
      } else {
        apcbTempBuf       = (UINT8 *)apcbTypeHeader;
        apcbTypeHeader    = (APCB_V3_TYPE_HEADER *)&apcbTempBuf[apcbTypeHeader->SizeOfType];
      }
    }
    apcbGroupHeader = (APCB_GROUP_HEADER *)apcbTypeHeader;
  }

  customPrint ("\t[CORE APCB ERR] APCB type not found\n");
  return CORE_APCB_ERR_TYPE_NOT_FOUND;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function retrieves a UINT16 APCB token
 *
 * @param[in]         apcbBuf         - Pointer to the APCB binary
 * @param[in]         priorityMask    - Priority Mask
 * @param[in]         boardMask       - Board Mask
 * @param[in]         typeInstance    - Type Instance
 * @param[in]         apcbToken       - APCB token ID
 * @param[out]        value16         - APCB token value
 *
 * @retval            CORE_APCB_OK
 *                    CORE_APCB_ERR_TOKEN_NOT_FOUND
 *
 */
CORE_APCB_RET_CODE
coreApcbGet16 (
  IN         UINT8        *apcbBuf,
  IN         UINT8        priorityMask,
  IN         UINT16       boardMask,
  IN         UINT8        typeInstance,
  IN         UINT32       apcbToken,
      OUT      UINT16     *value16
  )
{
  UINT8                 *dataBuf;
  UINT32                dataSize;
  APCB_TOKEN_PAIR       *tempPair;

  customPrint ("\t[CORE APCB INFO] coreApcbGet16 Entry\n");

  if (CORE_APCB_OK == coreApcbGetType (apcbBuf, APCB_GROUP_COMMON, APCB_TYPE_TOKEN_2BYTES, priorityMask, boardMask, typeInstance, &dataBuf, &dataSize)) {
    for (tempPair = (APCB_TOKEN_PAIR *)dataBuf; (UINT8 *)tempPair < &dataBuf[dataSize]; tempPair ++) {
      if (tempPair->token == apcbToken) {
        *value16 = tempPair->value.value16;
        customPrint ("\t[CORE APCB INFO] APCB token found: [%08X] = %08X\n", apcbToken, *value16);
        return CORE_APCB_OK;
      }
    }
  }

  customPrint ("\t[CORE APCB ERR] APCB token not found\n");
  return CORE_APCB_ERR_TOKEN_NOT_FOUND;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function sets a UINT16 APCB token
 *
 * @param[in]         apcbBuf         - Pointer to the APCB binary
 * @param[in]         priorityMask    - Priority Mask
 * @param[in]         boardMask       - Board Mask
 * @param[in]         typeInstance    - Type Instance
 * @param[in]         sizeApcbBuf     - Size of the input APCB buffer. The buffer has to be
 *                                      big enough for a new token/value pair to be added.
 * @param[in]         apcbToken       - APCB token ID
 * @param[in]         value16         - APCB token value
 *
 * @retval            CORE_APCB_OK
 *                    CORE_APCB_ERR_SPACE_NOT_ENOUGH
 *                    CORE_APCB_ERR_TYPE_NOT_FOUND
 *
 */
CORE_APCB_RET_CODE
coreApcbSet16 (
  IN  OUT    UINT8        *apcbBuf,
  IN  OUT    UINT32       sizeApcbBuf,
  IN         UINT8        priorityMask,
  IN         UINT16       boardMask,
  IN         UINT8        typeInstance,
  IN         UINT32       apcbToken,
  IN         UINT16       value16
  )
{
  UINT8                 *dataBuf;
  UINT32                dataSize;
  APCB_TOKEN_PAIR       *tempPair;
  APCB_V3_HEADER        *apcbHeader;
  APCB_GROUP_HEADER     *apcbGroupHeader;
  APCB_V3_TYPE_HEADER   *apcbTypeHeader;
  UINT8                 *apcbTempBuf;
  APCB_TOKEN_PAIR       *apcbInsertPair;
  UINT8                 *apcbEnding;
  UINT8                 *apcbGroupEnding;
  UINT32                *ApcbTail;
  UINT32                ApcbTailSizeInDword;
  UINT32                i;

  customPrint ("\t[CORE APCB INFO] coreApcbSet16 Entry\n");

  apcbTempBuf       = apcbBuf;
  apcbHeader        = (APCB_V3_HEADER *)apcbBuf;
  apcbEnding        = &apcbTempBuf[apcbHeader->SizeOfApcb];
  apcbGroupHeader   = (APCB_GROUP_HEADER *)&apcbHeader[1];

  if (APCB_SIGNATURE != apcbHeader->Signature) {
    customPrint ("\t[CORE APCB ERR] Invalid APCB data\n");
    return CORE_APCB_ERR_INVALID;
  }

  while ((UINT8 *)apcbGroupHeader < apcbEnding) {
    apcbTempBuf       = (UINT8 *)apcbGroupHeader;
    apcbGroupEnding   = &apcbTempBuf[apcbGroupHeader->SizeOfGroup];
    apcbTypeHeader    = (APCB_V3_TYPE_HEADER *)&apcbGroupHeader[1];
    while ((UINT8 *)apcbTypeHeader < apcbGroupEnding) {
      if (APCB_GROUP_COMMON == apcbTypeHeader->GroupId &&
          APCB_TYPE_TOKEN_2BYTES == apcbTypeHeader->TypeId &&
          typeInstance == apcbTypeHeader->InstanceId) {
        dataBuf          = (UINT8 *)&apcbTypeHeader[1];
        apcbInsertPair   = (APCB_TOKEN_PAIR *)dataBuf;
        dataSize         = apcbTypeHeader->SizeOfType - sizeof (APCB_V3_TYPE_HEADER);
        for (tempPair = (APCB_TOKEN_PAIR *)dataBuf; (UINT8 *)tempPair < &dataBuf[dataSize]; tempPair ++) {
          if (tempPair->token == apcbToken) {
            tempPair->value.value16 = value16;
            customPrint ("\t[CORE APCB INFO] APCB token set: [%08X] = %08X\n", apcbToken, value16);
            return CORE_APCB_OK;
          } else if (tempPair->token < apcbToken) {
            apcbInsertPair = &tempPair[1];
          }
        }

        if (sizeApcbBuf < apcbHeader->SizeOfApcb + sizeof (APCB_TOKEN_PAIR)) {
          customPrint ("\t[CORE APCB ERR] Not enough space to add a token\n");
          return CORE_APCB_ERR_SPACE_NOT_ENOUGH;
        }

        ApcbTailSizeInDword     = ((UINT32) (UINTN) (apcbEnding - (UINT8 *)apcbInsertPair)) / sizeof (UINT32);
        ApcbTail                = (UINT32 *)apcbInsertPair;
        for (i = 0; i < ApcbTailSizeInDword; i ++) {
          ApcbTail[ApcbTailSizeInDword - i + 1] = ApcbTail[ApcbTailSizeInDword - i - 1];
        }
        apcbInsertPair->token           = apcbToken;
        apcbInsertPair->value.value16   = value16;
        apcbTypeHeader->SizeOfType      += sizeof (APCB_TOKEN_PAIR);
        apcbGroupHeader->SizeOfGroup    += sizeof (APCB_TOKEN_PAIR);
        apcbHeader->SizeOfApcb += sizeof (APCB_TOKEN_PAIR);

        customPrint ("\t[CORE APCB INFO] APCB token appended: [%08X] = %08X\n", apcbToken, value16);
        return CORE_APCB_OK;
      } else {
        apcbTempBuf       = (UINT8 *)apcbTypeHeader;
        apcbTypeHeader    = (APCB_V3_TYPE_HEADER *)&apcbTempBuf[apcbTypeHeader->SizeOfType];
      }
    }
    apcbGroupHeader = (APCB_GROUP_HEADER *)apcbTypeHeader;
  }

  customPrint ("\t[CORE APCB ERR] APCB type not found\n");
  return CORE_APCB_ERR_TYPE_NOT_FOUND;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function retrieves a UINT32 APCB token
 *
 * @param[in]         apcbBuf         - Pointer to the APCB binary
 * @param[in]         priorityMask    - Priority Mask
 * @param[in]         boardMask       - Board Mask
 * @param[in]         typeInstance    - Type Instance
 * @param[in]         apcbToken       - APCB token ID
 * @param[out]        value32         - APCB token value
 *
 * @retval            CORE_APCB_OK
 *                    CORE_APCB_ERR_TOKEN_NOT_FOUND
 *
 */
CORE_APCB_RET_CODE
coreApcbGet32 (
  IN          UINT8       *apcbBuf,
  IN          UINT8       priorityMask,
  IN          UINT16      boardMask,
  IN          UINT8       typeInstance,
  IN          UINT32      apcbToken,
      OUT     UINT32      *value32
  )
{
  UINT8                 *dataBuf;
  UINT32                dataSize;
  APCB_TOKEN_PAIR       *tempPair;

  customPrint ("\t[CORE APCB INFO] coreApcbGet32 Entry\n");

  if (CORE_APCB_OK == coreApcbGetType (apcbBuf, APCB_GROUP_COMMON, APCB_TYPE_TOKEN_4BYTES, priorityMask, boardMask, typeInstance, &dataBuf, &dataSize)) {
    for (tempPair = (APCB_TOKEN_PAIR *)dataBuf; (UINT8 *)tempPair < &dataBuf[dataSize]; tempPair ++) {
      if (tempPair->token == apcbToken) {
        *value32 = tempPair->value.value32;
        customPrint ("\t[CORE APCB INFO] APCB token found: [%08X] = %08X\n", apcbToken, *value32);
        return CORE_APCB_OK;
      }
    }
  }

  customPrint ("\t[CORE APCB ERR] APCB token not found\n");
  return CORE_APCB_ERR_TOKEN_NOT_FOUND;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function sets a UINT32 APCB token
 *
 * @param[in]         apcbBuf         - Pointer to the APCB binary
 * @param[in]         priorityMask    - Priority Mask
 * @param[in]         boardMask       - Board Mask
 * @param[in]         typeInstance    - Type Instance
 * @param[in]         sizeApcbBuf     - Size of the input APCB buffer. The buffer has to be
 *                                      big enough for a new token/value pair to be added.
 * @param[in]         apcbToken       - APCB token ID
 * @param[in]         value16         - APCB token value
 *
 * @retval            CORE_APCB_OK
 *                    CORE_APCB_ERR_SPACE_NOT_ENOUGH
 *                    CORE_APCB_ERR_TYPE_NOT_FOUND
 *
 */
CORE_APCB_RET_CODE
coreApcbSet32 (
  IN  OUT     UINT8       *apcbBuf,
  IN  OUT     UINT32      sizeApcbBuf,
  IN          UINT8       priorityMask,
  IN          UINT16      boardMask,
  IN          UINT8       typeInstance,
  IN          UINT32      apcbToken,
  IN          UINT32      value32
    )
{
  UINT8                 *dataBuf;
  UINT32                dataSize;
  APCB_TOKEN_PAIR       *tempPair;
  APCB_V3_HEADER        *apcbHeader;
  APCB_GROUP_HEADER     *apcbGroupHeader;
  APCB_V3_TYPE_HEADER   *apcbTypeHeader;
  UINT8                 *apcbTempBuf;
  APCB_TOKEN_PAIR       *apcbInsertPair;
  UINT8                 *apcbEnding;
  UINT8                 *apcbGroupEnding;
  UINT32                *ApcbTail;
  UINT32                ApcbTailSizeInDword;
  UINT32                i;

  customPrint ("\t[CORE APCB INFO] coreApcbSet32 Entry\n");

  apcbTempBuf       = apcbBuf;
  apcbHeader        = (APCB_V3_HEADER *)apcbBuf;
  apcbEnding        = &apcbTempBuf[apcbHeader->SizeOfApcb];
  apcbGroupHeader   = (APCB_GROUP_HEADER *)&apcbHeader[1];

  if (APCB_SIGNATURE != apcbHeader->Signature) {
    customPrint ("\t[CORE APCB ERR] Invalid APCB data\n");
    return CORE_APCB_ERR_INVALID;
  }

  while ((UINT8 *)apcbGroupHeader < apcbEnding) {
    apcbTempBuf       = (UINT8 *)apcbGroupHeader;
    apcbGroupEnding   = &apcbTempBuf[apcbGroupHeader->SizeOfGroup];
    apcbTypeHeader    = (APCB_V3_TYPE_HEADER *)&apcbGroupHeader[1];
    while ((UINT8 *)apcbTypeHeader < apcbGroupEnding) {
      if (APCB_GROUP_COMMON == apcbTypeHeader->GroupId &&
          APCB_TYPE_TOKEN_4BYTES == apcbTypeHeader->TypeId &&
          typeInstance == apcbTypeHeader->InstanceId) {
        dataBuf          = (UINT8 *)&apcbTypeHeader[1];
        apcbInsertPair   = (APCB_TOKEN_PAIR *)dataBuf;
        dataSize         = apcbTypeHeader->SizeOfType - sizeof (APCB_V3_TYPE_HEADER);
        for (tempPair = (APCB_TOKEN_PAIR *)dataBuf; (UINT8 *)tempPair < &dataBuf[dataSize]; tempPair ++) {
          if (tempPair->token == apcbToken) {
            tempPair->value.value32 = value32;
            customPrint ("\t[CORE APCB INFO] APCB token set: [%08X] = %08X\n", apcbToken, value32);
            return CORE_APCB_OK;
          } else if (tempPair->token < apcbToken) {
            apcbInsertPair = &tempPair[1];
          }
        }

        if (sizeApcbBuf < apcbHeader->SizeOfApcb + sizeof (APCB_TOKEN_PAIR)) {
          customPrint ("\t[CORE APCB ERR] Not enough space to add a token\n");
          return CORE_APCB_ERR_SPACE_NOT_ENOUGH;
        }

        ApcbTailSizeInDword     = ((UINT32) (UINTN) (apcbEnding - (UINT8 *)apcbInsertPair)) / sizeof (UINT32);
        ApcbTail                = (UINT32 *)apcbInsertPair;
        for (i = 0; i < ApcbTailSizeInDword; i ++) {
          ApcbTail[ApcbTailSizeInDword - i + 1] = ApcbTail[ApcbTailSizeInDword - i - 1];
        }
        apcbInsertPair->token           = apcbToken;
        apcbInsertPair->value.value32   = value32;
        apcbTypeHeader->SizeOfType      += sizeof (APCB_TOKEN_PAIR);
        apcbGroupHeader->SizeOfGroup    += sizeof (APCB_TOKEN_PAIR);
        apcbHeader->SizeOfApcb += sizeof (APCB_TOKEN_PAIR);

        customPrint ("\t[CORE APCB INFO] APCB token appended: [%08X] = %08X\n", apcbToken, value32);
        return CORE_APCB_OK;
      } else {
        apcbTempBuf       = (UINT8 *)apcbTypeHeader;
        apcbTypeHeader    = (APCB_V3_TYPE_HEADER *)&apcbTempBuf[apcbTypeHeader->SizeOfType];
      }
    }
    apcbGroupHeader = (APCB_GROUP_HEADER *)apcbTypeHeader;
  }

  customPrint ("\t[CORE APCB ERR] APCB type not found\n");
  return CORE_APCB_ERR_TYPE_NOT_FOUND;
}

VOID
coreApcbFreeTypeChain (
  IN          CORE_APCB_TYPE_ENTRY  *coreApcbType
  )
{
  if (NULL != coreApcbType) {
    if (NULL != coreApcbType->next) {
      coreApcbFreeTypeChain (coreApcbType->next);
    } else {
      customFree (coreApcbType);
    }
  }
}

VOID
coreApcbFreeTokenChain (
  IN          CORE_APCB_TOKEN_ENTRY  *coreApcbToken
  )
{
  if (NULL != coreApcbToken) {
    if (NULL != coreApcbToken->next) {
      coreApcbFreeTokenChain (coreApcbToken->next);
    }
    customFree (coreApcbToken);
  }
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function retrieves the first type of APCB
 *
 * @param[in]         apcbBuf    - Pointer to the APCB binary
 * @param[out]        groupId    - Group Id of the first type
 * @param[out]        typeId     - Type Id of the first type
 * @param[out]        priorityMask - Priority Mask
 * @param[out]        boardMask    - Board Mask
 * @param[out]        instance   - Instance Id of the first type
 * @param[out]        dataBuf    - Pointer to the data of the first type
 * @param[out]        dataSize   - size of data of the first type
 * @param[out]        typeHandle - Handle of the first type, used to retrieve subsequent types
 *
 * @retval            CORE_APCB_OK
 *                    CORE_APCB_ERR_INVALID
 *                    CORE_APCB_ERR_GROUP_INVALID
 *                    CORE_APCB_ERR_TYPE_INVALID
 *                    CORE_APCB_ERR_SPACE_NOT_ENOUGH
 *
 */
CORE_APCB_RET_CODE
coreApcbGetFirstType (
  IN        UINT8       *apcbBuf,
      OUT   UINT16      *groupId,
      OUT   UINT16      *typeId,
      OUT   UINT8       *priorityMask,
      OUT   UINT16      *boardMask,
      OUT   UINT16      *instance,
      OUT   UINT8       **dataBuf,
      OUT   UINT32      *dataSize,
      OUT   UINT32      *typeHandle
  )
{
  APCB_V3_HEADER        *apcbHeader;
  APCB_GROUP_HEADER     *apcbGroupHeader;
  APCB_V3_TYPE_HEADER   *apcbTypeHeader;
  UINT8                 *apcbTempBuf;
  UINT8                 *apcbEnding;
  UINT8                 *apcbGroupEnding;
  UINT8                 *apcbTypeEnding;
  CORE_APCB_TYPE_ENTRY  *apcbTypeOrigin;

  customPrint ("\t[CORE APCB INFO] coreApcbGetFirstType Entry\n");

  customGetTypeCoreDb (&apcbTypeOrigin);
  coreApcbFreeTypeChain (apcbTypeOrigin);

  apcbTempBuf       = apcbBuf;
  apcbHeader        = (APCB_V3_HEADER *)apcbBuf;
  apcbEnding        = &apcbTempBuf[apcbHeader->SizeOfApcb];
  apcbGroupHeader   = (APCB_GROUP_HEADER *)&apcbHeader[1];
  apcbTypeHeader    = (APCB_V3_TYPE_HEADER *)&apcbGroupHeader[1];

  if (APCB_SIGNATURE != apcbHeader->Signature) {
    customPrint ("\t[CORE APCB ERR] Invalid APCB data\n");
    return CORE_APCB_ERR_INVALID;
  }

  apcbTempBuf       = (UINT8 *)apcbGroupHeader;
  apcbGroupEnding   = &apcbTempBuf[apcbGroupHeader->SizeOfGroup];
  if (apcbGroupEnding > apcbEnding) {
    customPrint ("\t[CORE APCB ERR] Invalid first APCB group\n");
    return CORE_APCB_ERR_GROUP_INVALID;
  }

  apcbTempBuf       = (UINT8 *)apcbTypeHeader;
  apcbTypeEnding    = &apcbTempBuf[apcbTypeHeader->SizeOfType];
  if (apcbTypeEnding > apcbGroupEnding) {
    customPrint ("\t[CORE APCB ERR] Invalid first APCB type\n");
    return CORE_APCB_ERR_TYPE_INVALID;
  }

  apcbTypeOrigin    = (CORE_APCB_TYPE_ENTRY *)customAlloc (sizeof (CORE_APCB_TYPE_ENTRY));
  if (NULL == apcbTypeOrigin) {
    customPrint ("\t[CORE APCB ERR] Not enough space for core type data\n");
    return CORE_APCB_ERR_SPACE_NOT_ENOUGH;
  }

  apcbTypeOrigin->next            = NULL;
  apcbTypeOrigin->typeHandle      = 1;
  apcbTypeOrigin->groupId         = apcbTypeHeader->GroupId;
  apcbTypeOrigin->typeId          = apcbTypeHeader->TypeId;
  apcbTypeOrigin->instance        = apcbTypeHeader->InstanceId;
  apcbTypeOrigin->dataBuf         = (UINT8 *)&apcbTypeHeader[1];
  apcbTypeOrigin->dataSize        = apcbTypeHeader->SizeOfType - sizeof (APCB_V3_TYPE_HEADER);
  apcbTypeOrigin->apcbGroupEnding = apcbGroupEnding;
  apcbTypeOrigin->apcbEnding      = apcbEnding;

  *groupId                        = apcbTypeHeader->GroupId;
  *typeId                         = apcbTypeHeader->TypeId;
  *instance                       = apcbTypeHeader->InstanceId;
  *dataBuf                        = (UINT8 *)&apcbTypeHeader[1];
  *dataSize                       = apcbTypeHeader->SizeOfType - sizeof (APCB_V3_TYPE_HEADER);
  *typeHandle                     = 1;

  customPrint ("\t[CORE APCB INFO] The first type: GroupId = 0x%x, TypeId = 0x%x, InstanceId = %d, dataBuf = %08X, dataSize = %08X\n",
                  *groupId, *typeId, *instance, *dataBuf, *dataSize);

  customSetTypeCoreDb (apcbTypeOrigin);

  return CORE_APCB_OK;
}


/*---------------------------------------------------------------------------------------*/
/**
 *      This function retrieves the APCB type next to that of the current handle
 *
 * @param[in, out]    typeHandle      - Handle of the current type and passed out as the token to retrieve the subsequent type
 * @param[out]        groupId         - Group Id of the next type
 * @param[out]        typeId          - Type Id of the next type
 * @param[out]        priorityMask    - Priority Mask
 * @param[out]        boardMask       - Board Mask
 * @param[out]        instance        - Instance Id of the next type
 * @param[out]        dataBuf         - Pointer to the data of the first type
 * @param[out]        dataSize        - size of data of the first type
 *
 * @retval            CORE_APCB_OK
 *                    CORE_APCB_ERR_LAST_TYPE
 *                    CORE_APCB_ERR_NO_ORIGIN_TYPE
 *                    CORE_APCB_ERR_INVALID_TYPE_HANDLE
 *                    CORE_APCB_ERR_GROUP_INVALID
 *                    CORE_APCB_ERR_TYPE_INVALID
 *                    CORE_APCB_ERR_SPACE_NOT_ENOUGH
 *
 */
CORE_APCB_RET_CODE
coreApcbGetNextType (
  IN  OUT     UINT32      *typeHandle,
      OUT     UINT16      *groupId,
      OUT     UINT16      *typeId,
      OUT     UINT8       *priorityMask,
      OUT     UINT16      *boardMask,
      OUT     UINT16      *instance,
      OUT     UINT8       **dataBuf,
      OUT     UINT32      *dataSize
  )
{
  UINT8                 *apcbTempBuf;
  UINT8                 *apcbTypeEnding;
  UINT8                 *apcbGroupEnding;
  APCB_GROUP_HEADER     *apcbGroupHeader;
  APCB_V3_TYPE_HEADER   *apcbTypeHeader;
  CORE_APCB_TYPE_ENTRY  *apcbTypeOrigin;
  CORE_APCB_TYPE_ENTRY  *currentApcbType;
  CORE_APCB_TYPE_ENTRY  *newApcbType;

  customPrint ("\t[CORE APCB INFO] coreApcbGetNextType Entry\n");

  apcbTypeOrigin      = NULL;
  customGetTypeCoreDb (&apcbTypeOrigin);

  if (NULL == apcbTypeOrigin) {
    customPrint ("\t[CORE APCB ERR] Call coreApcbGetFirstType to retrieve the first type first\n");
    return CORE_APCB_ERR_NO_ORIGIN_TYPE;
  }

  currentApcbType = apcbTypeOrigin;
  while (currentApcbType->typeHandle != *typeHandle) {
    if (currentApcbType->next == NULL) {
      customPrint ("\t[CORE APCB ERR] The type handle is invalid\n");
      return CORE_APCB_ERR_INVALID_TYPE_HANDLE;
    }
    currentApcbType = currentApcbType->next;
  }

  if (NULL != currentApcbType->next) {
    currentApcbType   = currentApcbType->next;
    *groupId          = currentApcbType->groupId;
    *typeId           = currentApcbType->typeId;
    *instance         = currentApcbType->instance;
    *dataBuf          = currentApcbType->dataBuf;
    *dataSize         = currentApcbType->dataSize;
    *typeHandle       = currentApcbType->typeHandle + 1;

    customPrint ("\t[CORE APCB INFO] The next type: GroupId = 0x%x, TypeId = 0x%x, InstanceId = %d, dataBuf = %08X, dataSize = %08X\n",
                    *groupId, *typeId, *instance, *dataBuf, *dataSize);

    return CORE_APCB_OK;
  }

  apcbTempBuf       = &currentApcbType->dataBuf[currentApcbType->dataSize];
  apcbTypeHeader    = (APCB_V3_TYPE_HEADER *)apcbTempBuf;
  apcbGroupEnding   = currentApcbType->apcbGroupEnding;

  if (apcbTempBuf >= currentApcbType->apcbEnding) {
    customPrint ("\t[CORE APCB ERR] This is already the last APCB type\n");
    return CORE_APCB_ERR_LAST_TYPE;
  }

  if (apcbTempBuf >= apcbGroupEnding) {
    //
    // This is the beginning of a new group
    //
    apcbGroupHeader   = (APCB_GROUP_HEADER *)apcbTempBuf;
    apcbTypeHeader    = (APCB_V3_TYPE_HEADER *)&apcbGroupHeader[1];
    apcbTempBuf       = (UINT8 *)apcbGroupHeader;
    apcbGroupEnding   = &apcbTempBuf[apcbGroupHeader->SizeOfGroup];
    if (apcbGroupEnding > currentApcbType->apcbEnding) {
      customPrint ("\t[CORE APCB ERR] Invalid APCB group\n");
      return CORE_APCB_ERR_GROUP_INVALID;
    }
    apcbTempBuf       = (UINT8 *)apcbTypeHeader;
  }

  apcbTypeEnding    = &apcbTempBuf[apcbTypeHeader->SizeOfType];
  if (apcbTypeEnding > apcbGroupEnding) {
    customPrint ("\t[CORE APCB ERR] Invalid APCB type\n");
    return CORE_APCB_ERR_TYPE_INVALID;
  }

  newApcbType       = (CORE_APCB_TYPE_ENTRY *)customAlloc (sizeof (CORE_APCB_TYPE_ENTRY));
  if (NULL == newApcbType) {
    customPrint ("\t[CORE APCB ERR] Not enough space for core type data\n");
    return CORE_APCB_ERR_SPACE_NOT_ENOUGH;
  }

  currentApcbType->next           = newApcbType;
  newApcbType->next               = NULL;
  newApcbType->typeHandle         = currentApcbType->typeHandle + 1;
  newApcbType->groupId            = apcbTypeHeader->GroupId;
  newApcbType->typeId             = apcbTypeHeader->TypeId;
  newApcbType->instance           = apcbTypeHeader->InstanceId;
  newApcbType->dataBuf            = (UINT8 *)&apcbTypeHeader[1];
  newApcbType->dataSize           = apcbTypeHeader->SizeOfType - sizeof (APCB_V3_TYPE_HEADER);
  newApcbType->apcbGroupEnding    = apcbGroupEnding;
  newApcbType->apcbEnding         = currentApcbType->apcbEnding;

  *groupId                        = apcbTypeHeader->GroupId;
  *typeId                         = apcbTypeHeader->TypeId;
  *instance                       = apcbTypeHeader->InstanceId;
  *dataBuf                        = (UINT8 *)&apcbTypeHeader[1];
  *dataSize                       = apcbTypeHeader->SizeOfType - sizeof (APCB_V3_TYPE_HEADER);
  *typeHandle                     = currentApcbType->typeHandle + 1;

  customPrint ("\t[CORE APCB INFO] The next type: GroupId = 0x%x, TypeId = 0x%x, InstanceId = %d, dataBuf = %08X, dataSize = %08X\n",
                  *groupId, *typeId, *instance, *dataBuf, *dataSize);

  return CORE_APCB_OK;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function retrieves the APCB type by the specified attributes
 *
 * @param[in]         apcbBuf         - Pointer to the APCB binary
 * @param[in]         groupId         - Group Id of the specified type
 * @param[in]         typeId          - Type Id of the specified type
 * @param[in]         priorityMask    - Priority Mask
 * @param[in]         boardMask       - Board Mask
 * @param[in]         instance        - Instance Id of the specified type
 * @param[out]        dataBuf         - Pointer to the data of the specified type
 * @param[out]        dataSize        - size of data of the specified type
 *
 * @retval            CORE_APCB_OK
 *                    CORE_APCB_ERR_INVALID
 *                    CORE_APCB_ERR_TYPE_NOT_FOUND
 *
 */
CORE_APCB_RET_CODE
coreApcbGetType (
  IN           UINT8       *apcbBuf,
  IN           UINT16      groupId,
  IN           UINT16      typeId,
  IN           UINT8       priorityMask,
  IN           UINT16      boardMask,
  IN           UINT16      instance,
      OUT      UINT8       **dataBuf,
      OUT      UINT32      *dataSize
  )
{
  APCB_V3_HEADER        *apcbHeader;
  APCB_GROUP_HEADER     *apcbGroupHeader;
  APCB_V3_TYPE_HEADER   *apcbTypeHeader;
  UINT8                 *apcbTempBuf;
  UINT8                 *apcbEnding;
  UINT8                 *apcbGroupEnding;

  customPrint ("\t[CORE APCB INFO] coreApcbGetType Entry\n");

  apcbTempBuf       = apcbBuf;
  apcbHeader        = (APCB_V3_HEADER *)apcbBuf;
  apcbEnding        = &apcbTempBuf[apcbHeader->SizeOfApcb];
  apcbGroupHeader   = (APCB_GROUP_HEADER *)&apcbHeader[1];

  if (APCB_SIGNATURE != apcbHeader->Signature) {
    customPrint ("\t[CORE APCB ERR] Invalid APCB data\n");
    return CORE_APCB_ERR_INVALID;
  }

  while ((UINT8 *)apcbGroupHeader < apcbEnding) {
    apcbTempBuf       = (UINT8 *)apcbGroupHeader;
    apcbGroupEnding   = &apcbTempBuf[apcbGroupHeader->SizeOfGroup];
    apcbTypeHeader    = (APCB_V3_TYPE_HEADER *)&apcbGroupHeader[1];
    while ((UINT8 *)apcbTypeHeader < apcbGroupEnding) {
      if (groupId == apcbTypeHeader->GroupId && typeId == apcbTypeHeader->TypeId && instance == apcbTypeHeader->InstanceId) {
        *dataBuf          = (UINT8 *)&apcbTypeHeader[1];
        *dataSize         = apcbTypeHeader->SizeOfType - sizeof (APCB_V3_TYPE_HEADER);
        customPrint ("\t[CORE APCB INFO] APCB type found: GroupId = 0x%x, TypeId = 0x%x, InstanceId = %d, dataBuf = %08X, dataSize = %08X\n",
                          groupId, typeId, instance, *dataBuf, *dataSize);
        return CORE_APCB_OK;
      } else {
        apcbTempBuf       = (UINT8 *)apcbTypeHeader;
        apcbTypeHeader    = (APCB_V3_TYPE_HEADER *)&apcbTempBuf[apcbTypeHeader->SizeOfType];
      }
    }
    apcbGroupHeader = (APCB_GROUP_HEADER *)apcbTypeHeader;
  }

  customPrint ("\t[CORE APCB ERR] APCB type not found\n");
  return CORE_APCB_ERR_TYPE_NOT_FOUND;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function sets the APCB type of the specified attributes
 *
 * @param[in]         apcbBuf         - Pointer to the APCB binary
 * @param[in]         sizeApcbBuf     - Size of the input APCB buffer. The buffer has to be
 *                                      big enough for the new type data to be substituted.
 * @param[in]         groupId         - Group Id of the specified type
 * @param[in]         typeId          - Type Id of the specified type
 * @param[in]         priorityMask    - Priority Mask
 * @param[in]         boardMask       - Board Mask
 * @param[in]         instance        - Instance Id of the specified type
 * @param[in]         dataBuf         - Pointer to the data of the specified type to be set
 * @param[in]         dataSize        - size of data of the specified type to be set
 *
 * @retval            CORE_APCB_OK
 *                    CORE_APCB_ERR_INVALID
 *                    CORE_APCB_ERR_TYPE_NOT_FOUND
 *
 */
CORE_APCB_RET_CODE
coreApcbSetType (
  IN           UINT8       *apcbBuf,
  IN  OUT      UINT32      sizeApcbBuf,
  IN           UINT16      groupId,
  IN           UINT16      typeId,
  IN           UINT8       priorityMask,
  IN           UINT16      boardMask,
  IN           UINT16      instance,
  IN           UINT8       *dataBuf,
  IN           UINT32      dataSize
  )
{
  APCB_V3_HEADER        *apcbHeader;
  APCB_GROUP_HEADER     *apcbGroupHeader;
  APCB_V3_TYPE_HEADER   *apcbTypeHeader;
  UINT8                 *apcbTempBuf;
  UINT8                 *apcbEnding;
  UINT8                 *apcbGroupEnding;
  UINT8                 *dataBuf0;
  UINT32                dataSize0;
  UINT32                *ApcbTail;
  UINT32                ApcbTailSizeInDword;
  UINT32                delta32;
  UINT32                i;

  customPrint ("\t[CORE APCB INFO] coreApcbSetType Entry\n");

  apcbTempBuf       = apcbBuf;
  apcbHeader        = (APCB_V3_HEADER *)apcbBuf;
  apcbEnding        = &apcbTempBuf[apcbHeader->SizeOfApcb];
  apcbGroupHeader   = (APCB_GROUP_HEADER *)&apcbHeader[1];

  if (APCB_SIGNATURE != apcbHeader->Signature) {
    customPrint ("\t[CORE APCB ERR] Invalid APCB data\n");
    return CORE_APCB_ERR_INVALID;
  }

  while ((UINT8 *)apcbGroupHeader < apcbEnding) {
    apcbTempBuf       = (UINT8 *)apcbGroupHeader;
    apcbGroupEnding   = &apcbTempBuf[apcbGroupHeader->SizeOfGroup];
    apcbTypeHeader    = (APCB_V3_TYPE_HEADER *)&apcbGroupHeader[1];
    while ((UINT8 *)apcbTypeHeader < apcbGroupEnding) {
      if (groupId == apcbTypeHeader->GroupId && typeId == apcbTypeHeader->TypeId && instance == apcbTypeHeader->InstanceId) {
        dataBuf0          = (UINT8 *)&apcbTypeHeader[1];
        dataSize0         = apcbTypeHeader->SizeOfType - sizeof (APCB_V3_TYPE_HEADER);
        customPrint ("\t[CORE APCB INFO] APCB type found: GroupId = 0x%x, TypeId = 0x%x, InstanceId = %d, dataBuf = %08X, dataSize = %08X\n",
                          groupId, typeId, instance, dataBuf0, dataSize0);

        if ((dataSize & 0x3) != 0) {
          //
          // Align dataSize to be multiple of 4 bytes
          //
          dataSize = (dataSize & 0xFFFFFFFC) + 4;
        }
        if (sizeApcbBuf < apcbHeader->SizeOfApcb - dataSize0 + dataSize) {
          customPrint ("\t[CORE APCB ERR] Not enough space to set the specified type\n");
          return CORE_APCB_ERR_SPACE_NOT_ENOUGH;
        }

        ApcbTailSizeInDword     = ((UINT32) (UINTN) (apcbEnding - &dataBuf0[dataSize0])) / sizeof (UINT32);
        delta32 = (dataSize0 - dataSize) / sizeof (UINT32);
        if (dataSize > dataSize0) {
          ApcbTail = (UINT32 *)&dataBuf0[dataSize0];
          for (i = 0; i < ApcbTailSizeInDword; i ++) {
            ApcbTail[ApcbTailSizeInDword - i + delta32 - 1] = ApcbTail[ApcbTailSizeInDword - i - 1];
          }
        } else {
          ApcbTail = (UINT32 *)&dataBuf0[dataSize];
          for (i = 0; i < ApcbTailSizeInDword; i ++) {
            ApcbTail[i] = ApcbTail[i + delta32];
          }
        }
        for (i = 0; i < dataSize; i ++) {
          dataBuf0[i] = dataBuf[i];
        }
        apcbTypeHeader->SizeOfType      = apcbTypeHeader->SizeOfType - (UINT16) dataSize0 + (UINT16) dataSize;
        apcbGroupHeader->SizeOfGroup    = apcbGroupHeader->SizeOfGroup - dataSize0 + dataSize;
        apcbHeader->SizeOfApcb          = apcbHeader->SizeOfApcb - dataSize0 + dataSize;

        return CORE_APCB_OK;
      } else {
        apcbTempBuf       = (UINT8 *)apcbTypeHeader;
        apcbTypeHeader    = (APCB_V3_TYPE_HEADER *)&apcbTempBuf[apcbTypeHeader->SizeOfType];
      }
    }
    apcbGroupHeader = (APCB_GROUP_HEADER *)apcbTypeHeader;
  }

  customPrint ("\t[CORE APCB ERR] APCB type not found\n");
  return CORE_APCB_ERR_TYPE_NOT_FOUND;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function retrieves the first APCB token
 *
 * @param[in]         typeHandle    - The type handle returned by coreApcbGetFirstType/coreApcbGetNextType
 * @param[out]        token         - token number
 * @param[out]        value         - token value
 * @param[out]        attribute     - attribute of the token: 0 - BOOL, 1- UINT8, 2 - UINT16, 3 - UINT32
 * @param[out]        tokenHandle   - Handle of the first token, used to retrieve subsequent token
 *
 * @retval            CORE_APCB_OK
 *                    CORE_APCB_ERR_NO_ORIGIN_TYPE
 *                    CORE_APCB_ERR_INVALID_TYPE_HANDLE
 *                    CORE_APCB_ERR_NON_APCB_TOKEN_CONTAINER
 *                    CORE_APCB_ERR_NO_MORE_TOKENS
 *
 */
CORE_APCB_RET_CODE
coreApcbGetFirstToken (
  IN          UINT32      typeHandle,
      OUT     UINT32      *token,
      OUT     VOID        *value,
      OUT     UINT8       *attribute,
      OUT     UINT32      *tokenHandle
  )
{
  UINT8                 *dataBuf;
  UINT32                dataSize;
  UINT32                handle;
  APCB_TOKEN_PAIR       *tempPair;
  CORE_APCB_TYPE_ENTRY  *apcbTypeOrigin;
  CORE_APCB_TYPE_ENTRY  *currentApcbType;
  CORE_APCB_TOKEN_ENTRY *apcbTokenOrigin;
  CORE_APCB_TOKEN_ENTRY *newApcbToken;
  CORE_APCB_TOKEN_ENTRY *previousApcbToken;
  BOOLEAN               firstApcbTokenHandled;
  CORE_APCB_RET_CODE    retSts;


  customPrint ("\t[CORE APCB INFO] coreApcbGetFirstToken Entry\n");

  retSts                  = CORE_APCB_ERR_NO_MORE_TOKENS;
  handle                  = 0;
  firstApcbTokenHandled   = FALSE;
  apcbTypeOrigin          = NULL;
  customGetTypeCoreDb (&apcbTypeOrigin);

  if (NULL == apcbTypeOrigin) {
    customPrint ("\t[CORE APCB ERR] Call coreApcbGetFirstType to retrieve the first type first\n");
    return CORE_APCB_ERR_NO_ORIGIN_TYPE;
  }

  customGetTokenCoreDb (&apcbTokenOrigin);
  coreApcbFreeTokenChain (apcbTokenOrigin);
  customSetTokenCoreDb (NULL);
  previousApcbToken   = NULL;

  currentApcbType     = apcbTypeOrigin;
  while (currentApcbType->typeHandle != typeHandle) {
    if (currentApcbType->next == NULL) {
      customPrint ("\t[CORE APCB ERR] The type handle is invalid\n");
      return CORE_APCB_ERR_INVALID_TYPE_HANDLE;
    }
    currentApcbType = currentApcbType->next;
  }

  if (currentApcbType->groupId != APCB_GROUP_COMMON) {
    customPrint ("\t[CORE APCB ERR] The type does not contain APCB tokens\n");
    return CORE_APCB_ERR_NON_APCB_TOKEN_CONTAINER;
  }

  dataBuf          = currentApcbType->dataBuf;
  dataSize         = currentApcbType->dataSize;

  for (tempPair = (APCB_TOKEN_PAIR *)dataBuf; (UINT8 *)tempPair < &dataBuf[dataSize]; tempPair ++) {
    if (!firstApcbTokenHandled) {
      *token = tempPair->token;
      switch (currentApcbType->typeId) {
        case APCB_TYPE_TOKEN_BOOLEAN:
          *(BOOLEAN *)value  = tempPair->value.bValue;
          *attribute        = 0;
          break;
        case APCB_TYPE_TOKEN_1BYTE:
          *(UINT8 *)value   = tempPair->value.value8;
          *attribute        = 1;
          break;
        case APCB_TYPE_TOKEN_2BYTES:
          *(UINT16 *)value  = tempPair->value.value16;
          *attribute        = 2;
          break;
        case APCB_TYPE_TOKEN_4BYTES:
          *(UINT32 *)value  = tempPair->value.value32;
          *attribute        = 3;
          break;
        default:
          customPrint ("\t[CORE APCB ERR] The type does not contain APCB tokens\n");
          return CORE_APCB_ERR_NON_APCB_TOKEN_CONTAINER;
      }
      firstApcbTokenHandled = TRUE;
      retSts                = CORE_APCB_OK;
    }

    newApcbToken = (CORE_APCB_TOKEN_ENTRY *)customAlloc (sizeof (CORE_APCB_TOKEN_ENTRY));
    if (NULL == newApcbToken) {
      customPrint ("\t[CORE APCB ERR] Not enough space for core token data\n");
      return CORE_APCB_ERR_SPACE_NOT_ENOUGH;
    }

    if (NULL == previousApcbToken) {
      customSetTokenCoreDb (newApcbToken);
    } else {
      previousApcbToken->next = newApcbToken;
    }
    newApcbToken->next                  = NULL;
    newApcbToken->tokenHandle           = handle ++;
    newApcbToken->pair.token            = tempPair->token;
    newApcbToken->pair.value.value32    = tempPair->value.value32;
    newApcbToken->attribute             = *attribute;
    previousApcbToken                   = newApcbToken;
  }

  if (firstApcbTokenHandled) {
    *tokenHandle                        = 1;
    customPrint ("\t[CORE APCB INFO] First APCB token found: [%08X] = %08X\n", *token, *(UINT32 *)value);
  }
  return retSts;
}


/*---------------------------------------------------------------------------------------*/
/**
 *      This function retrieves the next APCB token
 *
 * @param[in, out]    tokenHandle       - handle of the current token and passed out to retrieve the next token
 * @param[out]        token             - token number
 * @param[out]        value             - token value
 * @param[out]        attribute         - attribute of the token: 0 - BOOL, 1- UINT8, 2 - UINT16, 3 - UINT32
 *
 * @retval            CORE_APCB_OK
 *                    CORE_APCB_ERR_NO_MORE_TOKENS
 *
 */
CORE_APCB_RET_CODE
coreApcbGetNextToken (
  IN  OUT     UINT32      *tokenHandle,
      OUT     UINT32      *token,
      OUT     VOID        *value,
      OUT     UINT8       *attribute
  )
{
  CORE_APCB_TOKEN_ENTRY   *apcbTokenOrigin;
  CORE_APCB_TOKEN_ENTRY   *currentApcbToken;

  customPrint ("\t[CORE APCB INFO] coreApcbGetNextToken Entry\n");

  apcbTokenOrigin     = NULL;
  customGetTokenCoreDb (&apcbTokenOrigin);

  currentApcbToken    = apcbTokenOrigin;
  while (currentApcbToken->tokenHandle != *tokenHandle) {
    if (currentApcbToken->next == NULL) {
      customPrint ("\t[CORE APCB ERR] No more APCB tokens\n");
      return CORE_APCB_ERR_NO_MORE_TOKENS;
    }
    currentApcbToken = currentApcbToken->next;
  }

  *token              = currentApcbToken->pair.token;
  *(UINT32 *)value    = currentApcbToken->pair.value.value32;
  *attribute          = currentApcbToken->attribute;
  *tokenHandle        = currentApcbToken->tokenHandle + 1;
  customPrint ("\t[CORE APCB INFO] APCB token found: [%08X] = %08X\n", *token, *(UINT32 *)value);

  return CORE_APCB_OK;
}


