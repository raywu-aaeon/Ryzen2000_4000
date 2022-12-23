/* $NoKeywords:$ */
/**
 * @file
 *
 * APCB Lib V3.0
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
#include <Porting.h>
#include <Addendum/Apcb/Inc/SSP/APCB.h>
#include "CoreApcbInterface.h"
#include <Library/ApcbLibV3.h>
#include <Library/IdsLib.h>
#include <Filecode.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE        LIBRARY_APCBLIBV3_APCBLIBV3SERVICES_FILECODE
#define PRIORITY_MASK   0xFF
#define BOARD_MASK      0xFFFF
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
UINT8                   CurrentPriorityLevel          = INVALID_PRIORITY_LEVEL;
UINT8                   CurrentBiosDirEntry           = INVALID_BIOS_DIR_ENTRY;
UINT8                   CurrentBinaryInstance         = INVALID_BINARY_INSTANCE;
UINT8                   CurrentTypeInstance           = INVALID_TYPE_INSTANCE;

/*---------------------------------------------------------------------------------------*/
/**
 *      This function retrieves a boolean APCB token
 *
 * @param[in]         ApcbToken       - APCB token ID
 * @param[out]        Value           - APCB token value
 *
 * @retval            TRUE            - The token value is successfully retrived
 *                    FALSE           - The token cannot be found
 *
 */
BOOLEAN
ApcbGetBool (
  IN       UINT32        ApcbToken,
      OUT  BOOLEAN       *Value
  )
{
  UINT8         *ApcbBuf;
  UINT32        ApcbBufSize;

  ASSERT (INVALID_TYPE_INSTANCE != CurrentTypeInstance);

  ApcbBuf = (UINT8 *)GetApcbShadowCopy (&ApcbBufSize);
  if (NULL != ApcbBuf) {
    if (CORE_APCB_OK == coreApcbGetBool (ApcbBuf, PRIORITY_MASK, BOARD_MASK, CurrentTypeInstance, ApcbToken, Value)) {
      return TRUE;
    }
  }
  return FALSE;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function sets a boolean APCB token
 *
 * @param[in]         ApcbToken       - APCB token ID
 * @param[out]        Value           - APCB token value
 *
 * @retval            TRUE            - The token value is successfully set
 *                    FALSE           - The token cannot be set
 *
 */
BOOLEAN
ApcbSetBool (
  IN       UINT32        ApcbToken,
  IN       BOOLEAN       Value
  )
{
  UINT8         *ApcbBuf;
  UINT32        ApcbBufSize;

  ASSERT (INVALID_TYPE_INSTANCE != CurrentTypeInstance);

  ApcbBuf = (UINT8 *)GetApcbShadowCopy (&ApcbBufSize);
  if (NULL != ApcbBuf) {
    if (CORE_APCB_OK == coreApcbSetBool (ApcbBuf, ApcbBufSize, PRIORITY_MASK, BOARD_MASK, CurrentTypeInstance, ApcbToken, Value)) {
      return TRUE;
    }
  }

  return FALSE;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function retrieves a UINT8 APCB token
 *
 * @param[in]         ApcbToken       - APCB token ID
 * @param[out]        Value           - APCB token value
 *
 * @retval            TRUE            - The token value is successfully retrived
 *                    FALSE           - The token cannot be found
 *
 */
BOOLEAN
ApcbGet8 (
  IN       UINT32        ApcbToken,
      OUT  UINT8         *Value
  )
{
  UINT8         *ApcbBuf;
  UINT32        ApcbBufSize;

  ASSERT (INVALID_TYPE_INSTANCE != CurrentTypeInstance);

  ApcbBuf = (UINT8 *)GetApcbShadowCopy (&ApcbBufSize);
  if (NULL != ApcbBuf) {
    if (CORE_APCB_OK == coreApcbGet8 (ApcbBuf, PRIORITY_MASK, BOARD_MASK, CurrentTypeInstance, ApcbToken, Value)) {
      return TRUE;
    }
  }
  return FALSE;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function sets a UINT8 APCB token
 *
 * @param[in]         ApcbToken       - APCB token ID
 * @param[out]        Value           - APCB token value
 *
 * @retval            TRUE            - The token value is successfully set
 *                    FALSE           - The token cannot be set
 *
 */
BOOLEAN
ApcbSet8 (
  IN       UINT32        ApcbToken,
  IN       UINT8         Value
  )
{
  UINT8         *ApcbBuf;
  UINT32        ApcbBufSize;

  ASSERT (INVALID_TYPE_INSTANCE != CurrentTypeInstance);

  ApcbBuf = (UINT8 *)GetApcbShadowCopy (&ApcbBufSize);
  if (NULL != ApcbBuf) {
    if (CORE_APCB_OK == coreApcbSet8 (ApcbBuf, ApcbBufSize, PRIORITY_MASK, BOARD_MASK, CurrentTypeInstance, ApcbToken, Value)) {
      return TRUE;
    }
  }

  return FALSE;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function retrieves a UINT16 APCB token
 *
 * @param[in]         ApcbToken       - APCB token ID
 * @param[out]        Value           - APCB token value
 *
 * @retval            TRUE            - The token value is successfully retrived
 *                    FALSE           - The token cannot be found
 *
 */
BOOLEAN
ApcbGet16 (
  IN       UINT32        ApcbToken,
      OUT  UINT16        *Value
  )
{
  UINT8         *ApcbBuf;
  UINT32        ApcbBufSize;

  ASSERT (INVALID_TYPE_INSTANCE != CurrentTypeInstance);

  ApcbBuf = (UINT8 *)GetApcbShadowCopy (&ApcbBufSize);
  if (NULL != ApcbBuf) {
    if (CORE_APCB_OK == coreApcbGet16 (ApcbBuf, PRIORITY_MASK, BOARD_MASK, CurrentTypeInstance, ApcbToken, Value)) {
      return TRUE;
    }
  }
  return FALSE;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function sets a UINT16 APCB token
 *
 * @param[in]         ApcbToken       - APCB token ID
 * @param[out]        Value           - APCB token value
 *
 * @retval            TRUE            - The token value is successfully set
 *                    FALSE           - The token cannot be set
 *
 */
BOOLEAN
ApcbSet16 (
  IN       UINT32        ApcbToken,
  IN       UINT16        Value
  )
{
  UINT8         *ApcbBuf;
  UINT32        ApcbBufSize;

  ASSERT (INVALID_TYPE_INSTANCE != CurrentTypeInstance);

  ApcbBuf = (UINT8 *)GetApcbShadowCopy (&ApcbBufSize);
  if (NULL != ApcbBuf) {
    if (CORE_APCB_OK == coreApcbSet16 (ApcbBuf, ApcbBufSize, PRIORITY_MASK, BOARD_MASK, CurrentTypeInstance, ApcbToken, Value)) {
      return TRUE;
    }
  }

  return FALSE;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function retrieves a UINT32 APCB token
 *
 * @param[in]         ApcbToken       - APCB token ID
 * @param[out]        Value           - APCB token value
 *
 * @retval            TRUE            - The token value is successfully retrived
 *                    FALSE           - The token cannot be found
 *
 */
BOOLEAN
ApcbGet32 (
  IN       UINT32        ApcbToken,
      OUT  UINT32        *Value
  )
{
  UINT8         *ApcbBuf;
  UINT32        ApcbBufSize;

  ASSERT (INVALID_TYPE_INSTANCE != CurrentTypeInstance);

  ApcbBuf = (UINT8 *)GetApcbShadowCopy (&ApcbBufSize);
  if (NULL != ApcbBuf) {
    if (CORE_APCB_OK == coreApcbGet32 (ApcbBuf, PRIORITY_MASK, BOARD_MASK, CurrentTypeInstance, ApcbToken, Value)) {
      return TRUE;
    }
  }
  return FALSE;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function sets a UINT32 APCB token
 *
 * @param[in]         ApcbToken       - APCB token ID
 * @param[out]        Value           - APCB token value
 *
 * @retval            TRUE            - The token value is successfully set
 *                    FALSE           - The token cannot be set
 *
 */
BOOLEAN
ApcbSet32 (
  IN       UINT32        ApcbToken,
  IN       UINT32        Value
  )
{
  UINT8         *ApcbBuf;
  UINT32        ApcbBufSize;

  ASSERT (INVALID_TYPE_INSTANCE != CurrentTypeInstance);

  ApcbBuf = (UINT8 *)GetApcbShadowCopy (&ApcbBufSize);
  if (NULL != ApcbBuf) {
    if (CORE_APCB_OK == coreApcbSet32 (ApcbBuf, ApcbBufSize, PRIORITY_MASK, BOARD_MASK, CurrentTypeInstance, ApcbToken, Value)) {
      return TRUE;
    }
  }

  return FALSE;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function gets the data of a specified type
 *
 * @param[in]         GroupId         - Group ID
 * @param[in]         TypeId          - Type ID
 * @param[out]        DataBuf         - Pointer to the type data
 * @param[out]        DataSize        - Pointer to the size of the type data
 *
 * @retval            TRUE            - The type data is retrieved successfully
 *                    FALSE           - The type data cannot be retrieved
 *
 */
BOOLEAN
ApcbGetType (
  IN       UINT16        GroupId,
  IN       UINT16        TypeId,
      OUT  UINT8         **DataBuf,
      OUT  UINT32        *DataSize
  )
{
  UINT8         *ApcbBuf;
  UINT32        ApcbBufSize;

  ASSERT (INVALID_TYPE_INSTANCE != CurrentTypeInstance);

  ApcbBuf = (UINT8 *)GetApcbShadowCopy (&ApcbBufSize);
  if (NULL != ApcbBuf) {
    if (CORE_APCB_OK == coreApcbGetType (ApcbBuf, GroupId, TypeId, PRIORITY_MASK, BOARD_MASK, CurrentTypeInstance, DataBuf, DataSize)) {
      return TRUE;
    }
  }

  return FALSE;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function sets the data of a specified type
 *
 * @param[in]         GroupId         - Group ID
 * @param[in]         TypeId          - Type ID
 * @param[out]        DataBuf         - Pointer to the type data
 * @param[out]        DataSize        - Pointer to the size of the type data
 *
 * @retval            TRUE            - The type data is set successfully
 *                    FALSE           - The type data cannot be set
 *
 */
BOOLEAN
ApcbSetType (
  IN       UINT16        GroupId,
  IN       UINT16        TypeId,
  IN       UINT8         *DataBuf,
  IN       UINT32        DataSize
  )
{
  UINT8         *ApcbBuf;
  UINT32        ApcbBufSize;

  ASSERT (INVALID_TYPE_INSTANCE != CurrentTypeInstance);

  ApcbBuf = (UINT8 *)GetApcbShadowCopy (&ApcbBufSize);
  if (NULL != ApcbBuf) {
    if (CORE_APCB_OK == coreApcbSetType (ApcbBuf, ApcbBufSize, GroupId, TypeId, PRIORITY_MASK, BOARD_MASK, CurrentTypeInstance, DataBuf, DataSize)) {
      return TRUE;
    }
  }

  return FALSE;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function purges all tokens
 *
 *
 * @retval            TRUE            - The tokens are successfully purged
 *                    FALSE           - The tokens cannot be found
 *
 */
BOOLEAN
ApcbPurgeAllTokens (
  VOID
  )
{
  UINT8         *ApcbBuf;
  UINT32        ApcbBufSize;

  ASSERT (INVALID_TYPE_INSTANCE != CurrentTypeInstance);

  ApcbBuf = (UINT8 *)GetApcbShadowCopy (&ApcbBufSize);
  if (NULL != ApcbBuf) {
    if (CORE_APCB_OK != coreApcbSetType (ApcbBuf, ApcbBufSize, APCB_GROUP_TOKEN, APCB_TYPE_TOKEN_BOOLEAN, PRIORITY_MASK, BOARD_MASK, CurrentTypeInstance, NULL, 0)) {
      return FALSE;
    }
    if (CORE_APCB_OK != coreApcbSetType (ApcbBuf, ApcbBufSize, APCB_GROUP_TOKEN, APCB_TYPE_TOKEN_1BYTE, PRIORITY_MASK, BOARD_MASK, CurrentTypeInstance, NULL, 0)) {
      return FALSE;
    }
    if (CORE_APCB_OK != coreApcbSetType (ApcbBuf, ApcbBufSize, APCB_GROUP_TOKEN, APCB_TYPE_TOKEN_2BYTES, PRIORITY_MASK, BOARD_MASK, CurrentTypeInstance, NULL, 0)) {
      return FALSE;
    }
    if (CORE_APCB_OK != coreApcbSetType (ApcbBuf, ApcbBufSize, APCB_GROUP_TOKEN, APCB_TYPE_TOKEN_4BYTES, PRIORITY_MASK, BOARD_MASK, CurrentTypeInstance, NULL, 0)) {
      return FALSE;
    }
    return TRUE;
  }

  return FALSE;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function purges all types
 *
 *
 * @retval            TRUE            - The types are successfully purged
 *                    FALSE           - The types cannot be purged
 *
 */
BOOLEAN
ApcbPurgeAllTypes (
  VOID
  )
{
  UINT8         *ApcbBuf;
  UINT32        ApcbBufSize;
  UINT32        TypeHandle;
  UINT16        GroupId;
  UINT16        TypeId;
  UINT8         *DataBuf;
  UINT32        DataSize;
  UINT8         PriorityMask;
  UINT16        BoardMask;
  UINT16        TypeInstance;

  ASSERT (INVALID_TYPE_INSTANCE != CurrentTypeInstance);

  ApcbBuf = (UINT8 *)GetApcbShadowCopy (&ApcbBufSize);
  if (NULL != ApcbBuf) {
    while (TRUE) {
      if (CORE_APCB_OK == coreApcbGetFirstType (ApcbBuf, &GroupId, &TypeId, &PriorityMask, &BoardMask, &TypeInstance, &DataBuf, &DataSize, &TypeHandle)) {
        while (TRUE) {
          if (0 != DataSize && TypeInstance == CurrentTypeInstance) {
            if (ApcbSetType (GroupId, TypeId, NULL, 0)) {
              IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] Type data purged from GroupId = 0x%0x, TypeId = 0x%x, TypeInstanceId = 0x%x, 0x%x:0x%x\n",
                                          GroupId, TypeId, CurrentTypeInstance, DataBuf, DataSize);
              //
              // Restart type searching loop
              //
              break;
            } else {
              IDS_HDT_CONSOLE_PSP_TRACE ("[APCB Lib V3] Failed to purge type data from GroupId = 0x%0x, TypeId = 0x%x, TypeInstanceId = 0x%x, 0x%x:0x%x\n",
                                          GroupId, TypeId, CurrentTypeInstance, DataBuf, DataSize);
              return FALSE;
            }
          }
          if (CORE_APCB_OK != coreApcbGetNextType (&TypeHandle, &GroupId, &TypeId, &PriorityMask, &BoardMask, &TypeInstance, &DataBuf, &DataSize)) {
            //
            // No more APCB types found
            //
            return TRUE;
          }
        }
      } else {
        //
        // No more APCB types found
        //
        return TRUE;        
      }
    }
  }
  return TRUE;
}

/*---------------------------------------------------------------------------------------*/
/**
 *      This function demonstrates the usage of the following core APCB interfaces:
 *        - coreApcbGetFirstType
 *        - coreApcbGetNextType
 *        - coreApcbGetFirstToken
 *        - coreApcbGetNextToken
 *
 *
 * @retval            TRUE            - The tokens are successfully purged
 *                    FALSE           - The tokens cannot be found
 *
 */
BOOLEAN
ApcbEnumerateTokens (
  VOID
  )
{
  UINT8         *ApcbBuf;
  UINT32        ApcbBufSize;
  UINT32        TypeHandle;
  UINT32        TokenHandle;
  UINT16        GroupId;
  UINT16        TypeId;
  UINT8         PriorityMask;
  UINT16        BoardMask;
  UINT16        TypeInstanceId;
  UINT8         *DataBuf;
  UINT32        DataSize;
  UINT32        Token;
  UINT32        Value32;
  UINT8         Attribute;

  ASSERT (INVALID_TYPE_INSTANCE != CurrentTypeInstance);

  ApcbBuf = (UINT8 *)GetApcbShadowCopy (&ApcbBufSize);
  if (NULL != ApcbBuf) {
    if (CORE_APCB_OK == coreApcbGetFirstType (ApcbBuf, &GroupId, &TypeId, &PriorityMask, &BoardMask, &TypeInstanceId, &DataBuf, &DataSize, &TypeHandle)) {
      while (TRUE) {
        IDS_HDT_CONSOLE_PSP_TRACE ("[Demo] GroupId = 0x%0x, TypeId = 0x%x, TypeInstanceId = 0x%x, 0x%x:0x%x\n",
                                      GroupId, TypeId, TypeInstanceId, DataBuf, DataSize);
        if (CORE_APCB_OK == coreApcbGetFirstToken (TypeHandle, &Token, &Value32, &Attribute, &TokenHandle)) {
          while (TRUE) {
            IDS_HDT_CONSOLE_PSP_TRACE ("[Demo]\t\t\t %a [0x%0x] = 0x%x\n",
                                      (0 == Attribute) ? "BOOL" : ((1 == Attribute) ? "UINT8" : ((2 == Attribute) ? "UINT16" : "UINT32")),
                                      Token, Value32);
            if (CORE_APCB_OK != coreApcbGetNextToken (&TokenHandle, &Token, &Value32, &Attribute)) {
              break;
            }
          }
        }
        if (CORE_APCB_OK != coreApcbGetNextType (&TypeHandle, &GroupId, &TypeId, &PriorityMask, &BoardMask, &TypeInstanceId, &DataBuf, &DataSize)) {
          break;
        }
      }
    }
  }
  return TRUE;
}

