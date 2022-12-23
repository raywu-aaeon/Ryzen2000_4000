/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Library
 *
 * Contains interface to the AMD AGESA library
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
#include <Library/BaseLib.h>
#include <Library/AmdBaseLib.h>
#include <Library/ApcbZpLib.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/ApobCommonServiceLib.h>
#include <Filecode.h>

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */
#define FILECODE        LIBRARY_APCBZPLIB_GETSETPARAMS_FILECODE

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
extern UINT8                     mApcbInstance;
extern BOOLEAN                   mAtRuntime;
extern BOOLEAN                   mApcbRecoveryFlag;

extern
UINT8
ApcbCalcCheckSum (
  IN       VOID             *ApcbPtr,
  IN       UINT32           Length
  );


/*
 * Internal Function to retrieve APCB Data for given Type under a given Group
*/
EFI_STATUS
InternalApcbLocateType (
  IN       UINT16   GroupId,
  IN       UINT16   TypeId,
  IN       UINT16   InstanceId,
  IN       UINT32   *Size,
  IN OUT   VOID     **TypeData
  )
{
  APCB_HEADER         *ApcbHeader;
  UINT8               *ApcbEnding;
  APCB_GROUP_HEADER   *ApcbGroupHeader;
  APCB_TYPE_HEADER    *ApcbTypeHeader;

  IDS_HDT_CONSOLE_PSP_TRACE ("ApcbLocateType GroupId : 0x%04X,  TypeId : 0x%04X, InstanceId:0x%x\n", GroupId, TypeId, InstanceId);
  ApcbHeader = GetApcbShadowCopy ();
  ApcbEnding = (UINT8 *) ((UINT8 *) ApcbHeader + ApcbHeader->SizeOfApcb - 1);
  ApcbGroupHeader = (APCB_GROUP_HEADER *) (VOID *) ((UINT8 *) ApcbHeader + sizeof (APCB_HEADER));
  ApcbTypeHeader = (APCB_TYPE_HEADER *) (VOID *) ((UINT8 *) ApcbGroupHeader + sizeof (APCB_GROUP_HEADER));

  //
  // Travers all APCB Group and Type
  //
  while ((((UINT8 *) ApcbGroupHeader + sizeof (APCB_GROUP_HEADER) - 1) <= ApcbEnding) && ((UINT8 *) ((EFI_PHYSICAL_ADDRESS) ApcbTypeHeader + ApcbTypeHeader->SizeOfType - 1) <= ApcbEnding)) {
    if (ApcbGroupHeader->GroupId == GroupId) {
      if ((ApcbTypeHeader->TypeId == TypeId)  && (ApcbTypeHeader->InstanceId == InstanceId)) {
        *TypeData = (VOID *) ((EFI_PHYSICAL_ADDRESS) ApcbTypeHeader + sizeof (APCB_TYPE_HEADER));
        *Size = (ApcbTypeHeader->SizeOfType - sizeof (APCB_TYPE_HEADER));
        IDS_HDT_CONSOLE_PSP_TRACE ("\t\tFound matched type id @0x%x!\n", ApcbTypeHeader);
        return EFI_SUCCESS;
      } else {
        ApcbTypeHeader = (APCB_TYPE_HEADER *) ((EFI_PHYSICAL_ADDRESS) ApcbTypeHeader + ApcbTypeHeader->SizeOfType);
        // Adjust alignment
        ApcbTypeHeader = (APCB_TYPE_HEADER *) (UINT8 *) ApcbTypeHeader + ((ALIGN_SIZE_OF_TYPE - ((EFI_PHYSICAL_ADDRESS) ApcbTypeHeader) % ALIGN_SIZE_OF_TYPE) & (ALIGN_SIZE_OF_TYPE - 1));
        if ((UINT8 *) ApcbTypeHeader > (UINT8 *) ((EFI_PHYSICAL_ADDRESS) ApcbGroupHeader + ApcbGroupHeader->SizeOfGroup)) {
          return EFI_NOT_FOUND;
        }
      }
    } else {
      ApcbGroupHeader = (APCB_GROUP_HEADER *) ((EFI_PHYSICAL_ADDRESS) ApcbGroupHeader + ApcbGroupHeader->SizeOfGroup);
      // APCB Type header following APCP Group header should already be 4-bytes aligned, there's no need for extra adjustment on ApcbTypeHeader pointer.
      ApcbTypeHeader = (APCB_TYPE_HEADER *) (VOID *) ((CHAR8 *) ApcbGroupHeader + sizeof (APCB_GROUP_HEADER));
    }
  }

  return EFI_NOT_FOUND;
}

/*
 * Internal Function to retrieve an APCB Parameter detail info with a given type and token
 * If given token ID is not found, ParamAttribOffset &  ParamValueOffset will return the next offset of last valid elements
*/
EFI_STATUS
InternalApcbGetParameterDetails (
  IN       APCB_PARAM_TYPE    ApcbParamType,
  IN       UINT16             ApcbParamToken,
  IN OUT   UINT16             *GroupIdPtr,
  IN OUT   APCB_PARAM_ATTRIBUTE      **ApcbParamAttributeStreamPtr,
  IN OUT   UINT8                     **ApcbParamValueStreamPtr,
  IN OUT   UINT32                    *ParamAttribOffsetPtr,
  IN OUT   UINT32                    *ParamValueOffsetPtr
  )
{
  EFI_STATUS                Status;
  UINT16                    TokenBegin;
  UINT16                    TokenEnd;
  UINT16                    TokenLimit;
  UINT32                     i;
  UINT32                    ParamOffset;
  UINT8                     *ApcbParamValueStream;
  UINT32                    ApcbParamBlockSize;
  APCB_PARAM_ATTRIBUTE      *ApcbParamAttributeStream;

  //
  // Ensure the input type is legal
  //
  ASSERT (ApcbParamType >= APCB_PSP_TYPE_CONFIG_DEFAULT_PARAMETERS && ApcbParamType <= APCB_TYPE_CBS_DEBUG_DUMMY_PARAMETERS);
  if ((ApcbParamType < APCB_PSP_TYPE_CONFIG_DEFAULT_PARAMETERS) || (ApcbParamType > APCB_TYPE_CBS_DEBUG_DUMMY_PARAMETERS)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Invalid ApcbParamType\n");
    return EFI_INVALID_PARAMETER;
  }

  ASSERT ((GroupIdPtr != NULL) &&
          (ApcbParamAttributeStreamPtr != NULL) &&
          (ApcbParamValueStreamPtr != NULL) &&
          (ParamAttribOffsetPtr != NULL) &&
          (ParamValueOffsetPtr != NULL));

  if ((GroupIdPtr == NULL) ||
      (ApcbParamAttributeStreamPtr == NULL) ||
      (ApcbParamValueStreamPtr == NULL) ||
      (ParamAttribOffsetPtr == NULL) ||
      (ParamValueOffsetPtr == NULL)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Input parameters Pointer set to NULL\n");
    return EFI_INVALID_PARAMETER;
  }

  switch (ApcbParamType) {
  case APCB_PSP_TYPE_CONFIG_DEFAULT_PARAMETERS:
  case APCB_PSP_TYPE_CONFIG_PARAMETERS:
    *GroupIdPtr = APCB_GROUP_PSP;
    TokenBegin = APCB_TOKEN_CONFIG_PSP_BEGIN + 1;
    TokenEnd = APCB_TOKEN_CONFIG_PSP_END;
    TokenLimit = APCB_TOKEN_CONFIG_CCX_BEGIN - 1;
    break;

  case APCB_CCX_TYPE_CONFIG_DEFAULT_PARAMETERS:
  case APCB_CCX_TYPE_CONFIG_PARAMETERS:
    *GroupIdPtr = APCB_GROUP_CCX;
    TokenBegin = APCB_TOKEN_CONFIG_CCX_BEGIN + 1;
    TokenEnd = APCB_TOKEN_CONFIG_CCX_END;
    TokenLimit = APCB_TOKEN_CONFIG_DF_BEGIN - 1;
    break;

  case APCB_DF_TYPE_CONFIG_DEFAULT_PARAMETERS:
  case APCB_DF_TYPE_CONFIG_PARAMETERS:
    *GroupIdPtr = APCB_GROUP_DF;
    TokenBegin = APCB_TOKEN_CONFIG_DF_BEGIN + 1;
    TokenEnd = APCB_TOKEN_CONFIG_DF_END;
    TokenLimit = APCB_TOKEN_CONFIG_MEM_BEGIN - 1;
    break;

  case APCB_MEM_TYPE_CONFIG_DEFAULT_PARAMETERS:
  case APCB_MEM_TYPE_CONFIG_PARAMETERS:
    *GroupIdPtr = APCB_GROUP_MEMORY;
    TokenBegin = APCB_TOKEN_CONFIG_MEM_BEGIN + 1;
    TokenEnd = APCB_TOKEN_CONFIG_MEM_END;
    TokenLimit = APCB_TOKEN_CONFIG_GNB_BEGIN - 1;
    break;

  case APCB_GNB_TYPE_CONFIG_DEFAULT_PARAMETERS:
  case APCB_GNB_TYPE_CONFIG_PARAMETERS:
    *GroupIdPtr = APCB_GROUP_GNB;
    TokenBegin = APCB_TOKEN_CONFIG_GNB_BEGIN + 1;
    TokenEnd = APCB_TOKEN_CONFIG_GNB_END;
    TokenLimit = APCB_TOKEN_CONFIG_FCH_BEGIN - 1;
    break;

  case APCB_FCH_TYPE_CONFIG_DEFAULT_PARAMETERS:
  case APCB_FCH_TYPE_CONFIG_PARAMETERS:
    *GroupIdPtr = APCB_GROUP_FCH;
    TokenBegin = APCB_TOKEN_CONFIG_FCH_BEGIN + 1;
    TokenEnd = APCB_TOKEN_CONFIG_FCH_END;
    TokenLimit = APCB_TOKEN_CONFIG_LIMIT - 1;
    break;

  case APCB_TYPE_CBS_COMMON_PARAMETERS:
    *GroupIdPtr = APCB_GROUP_CBS;
    TokenBegin = APCB_TOKEN_CBS_CMN_BEGIN + 1;
    TokenEnd = APCB_TOKEN_CBS_CMN_END;
    TokenLimit = APCB_TOKEN_CBS_CMN_LIMIT - 1;
    break;

  case APCB_TYPE_CBS_DEBUG_PARAMETERS:
    *GroupIdPtr = APCB_GROUP_CBS;
    TokenBegin = APCB_TOKEN_CBS_DBG_BEGIN + 1;
    TokenEnd = APCB_TOKEN_CBS_DBG_END;
    TokenLimit = APCB_TOKEN_CBS_DBG_LIMIT - 1;
    break;

  default:
    IDS_HDT_CONSOLE_PSP_TRACE ("Invalid ApcbParamType\n");
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  Status = InternalApcbLocateType (*GroupIdPtr, ApcbParamType, 0, &ApcbParamBlockSize, (VOID *) &ApcbParamAttributeStream);
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Can't Locate ApcbParamType\n");
    return Status;
  }
  *ApcbParamAttributeStreamPtr = ApcbParamAttributeStream;

  // Get Value Stream offset
  i = 0;
  while (ApcbParamAttributeStream[i].Token != APCB_TOKEN_CONFIG_LIMIT) {
    //
    // The starting token of each component should remain constant across different versions of ABL
    //
    if ((ApcbParamAttributeStream[i].Token < TokenBegin || ApcbParamAttributeStream[i].Token >= TokenLimit)) {
      ASSERT (FALSE);
    }
    i ++;
  }
  ApcbParamValueStream = (UINT8 *) &ApcbParamAttributeStream[i + 1];
  *ApcbParamValueStreamPtr = ApcbParamValueStream;

  //
  // Search for Input Token
  //
  i = 0;
  ParamOffset = 0;
  while (ApcbParamAttributeStream[i].Token != APCB_TOKEN_CONFIG_LIMIT) {
    if (ApcbParamAttributeStream[i].Token < TokenEnd) {
      //
      // If the token exceeds the end set by the current ABL, it maybe a newly added token
      // and can be safely ignored in the current version
      //
      if (ApcbParamAttributeStream[i].Token == ApcbParamToken) {
        IDS_HDT_CONSOLE_PSP_TRACE ("Token found @ AttribOffset=%d ValueOffset=0x%x \n", i, ParamOffset);
        *ParamAttribOffsetPtr = i;
        *ParamValueOffsetPtr = ParamOffset;
        return EFI_SUCCESS;
      }
    }
    ParamOffset += (ApcbParamAttributeStream[i].Size + 1);
    i ++;
  }
  //Not found return the next offset of last valid elements
  *ParamAttribOffsetPtr = i;
  *ParamValueOffsetPtr = ParamOffset;
  return EFI_NOT_FOUND;
}
/*
 * Internal Function to retrieve an APCB Parameter with a given type and token
*/
EFI_STATUS
InternalApcbGetParameter (
  IN       APCB_PARAM_TYPE    ApcbParamType,
  IN       UINT16             ApcbParamToken,
  IN OUT   UINT32             *SizeInByte,
  IN OUT   VOID               *Value
  )
{
  EFI_STATUS                Status;
  UINT16                    GroupId;
  APCB_PARAM_ATTRIBUTE      *ApcbParamAttributeStream;
  UINT8*                    ApcbParamValueStream;
  UINT32                    ParamAttribOffset;
  UINT32                    ParamValueOffset;
  //
  // Ensure the input type is legal
  //
  ASSERT (ApcbParamType >= APCB_PSP_TYPE_CONFIG_DEFAULT_PARAMETERS && ApcbParamType <= APCB_TYPE_CBS_DEBUG_DUMMY_PARAMETERS);
  if ((ApcbParamType < APCB_PSP_TYPE_CONFIG_DEFAULT_PARAMETERS) || (ApcbParamType > APCB_TYPE_CBS_DEBUG_DUMMY_PARAMETERS)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Invalid ApcbParamType\n");
    return EFI_INVALID_PARAMETER;
  }

  ASSERT ((Value != NULL) && (SizeInByte != NULL));
  if ((Value == NULL) || (SizeInByte == NULL)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Parameter Pointer set to NULL\n");
    return EFI_INVALID_PARAMETER;
  }

  Status = InternalApcbGetParameterDetails (ApcbParamType, ApcbParamToken,
                                  &GroupId, &ApcbParamAttributeStream, &ApcbParamValueStream,
                                  &ParamAttribOffset, &ParamValueOffset);
  //Token has been found
  if (Status == EFI_SUCCESS) {
    *SizeInByte = ApcbParamAttributeStream[ParamAttribOffset].Size + 1;
    CopyMem (Value, ApcbParamValueStream + ParamValueOffset, *SizeInByte);
  }
  return Status;
}
/*
 * Internal Function to Set an APCB Parameter with a given type and token
*/
EFI_STATUS
InternalApcbSetParameter (
  IN       APCB_PARAM_TYPE    ApcbParamType,
  IN       UINT16             TokenId,
  IN OUT   UINT32           *SizeInByte,
  IN OUT   UINT64           *Value
  )
{
  EFI_STATUS                Status;
  UINT16                    GroupId;
  APCB_PARAM_ATTRIBUTE      *ApcbParamAttributeStream;
  UINT8                     *ApcbParamValueStream;
  UINT32                    ParamAttribOffset;
  UINT32                    ParamValueOffset;
  UINT8                     *NewApcbParamDataStart;
  UINT8                     *NewApcbParamData;
  UINT32                    NewApcbParamDataSize;
  UINT8                     *NewApcb;
  UINT32                    NewApcbSize;
  UINT16                    ApcbTypeSize;
  APCB_HEADER               *ApcbShadowCopy;

  ApcbParamValueStream = NULL;

  //Check if token already exist in the custom blob
  Status = InternalApcbGetParameterDetails (ApcbParamType, TokenId,
                                  &GroupId, &ApcbParamAttributeStream, &ApcbParamValueStream,
                                  &ParamAttribOffset, &ParamValueOffset);
  //Update the value, if token found
  if (EFI_SUCCESS == Status) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Token found in shadow copy\n");

    ASSERT ((ApcbParamAttributeStream[ParamAttribOffset].Size + 1) == *SizeInByte);
    //Return if size not match
    if ((ApcbParamAttributeStream[ParamAttribOffset].Size + 1) != *SizeInByte) {
      IDS_HDT_CONSOLE_PSP_TRACE ("Size mismatch\n");
      return EFI_UNSUPPORTED;
    }
    IDS_HDT_CONSOLE_PSP_TRACE ("Update Value &[%x]=%x\n", ApcbParamValueStream + ParamValueOffset, *Value);
    CopyMem (ApcbParamValueStream + ParamValueOffset, Value, *SizeInByte);
    ApcbShadowCopy = GetApcbShadowCopy ();
    ((APCB_HEADER *) ApcbShadowCopy)->CheckSumByte = 0;
    ((APCB_HEADER *) ApcbShadowCopy)->CheckSumByte = (UINT8) (~ApcbCalcCheckSum (ApcbShadowCopy, ((APCB_HEADER *) ApcbShadowCopy)->SizeOfApcb)) + 1;
    return EFI_SUCCESS;
  } else {
    //Compose new APCB Insert the value to tail if token not found
    //Allocate memory to hold size increased APCB type blob
    //ParamAttrib size need to add one additional byte to hold the end flag
    IDS_HDT_CONSOLE_PSP_TRACE ("Token not found in shadow copy, compose a new shadow copy and insert the token\n");
    ApcbTypeSize = ((APCB_TYPE_HEADER *) ((UINT8 *) ApcbParamAttributeStream - sizeof (APCB_TYPE_HEADER)))->SizeOfType;
    NewApcbParamDataSize = ApcbTypeSize - sizeof (APCB_TYPE_HEADER) + sizeof (APCB_PARAM_ATTRIBUTE)  + *SizeInByte + ALIGN_SIZE_OF_TYPE;
    NewApcbParamData = NULL;
    NewApcbParamData = AllocateZeroPool (NewApcbParamDataSize);
    IDS_HDT_CONSOLE_PSP_TRACE ("ALLOCATE[%x:%x]\n", NewApcbParamData, NewApcbParamDataSize);
    ASSERT (NewApcbParamData != NULL);
    if (NewApcbParamData == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    NewApcbParamDataStart = NewApcbParamData;
    //Copy Original Attrib data
    CopyMem (NewApcbParamData, ApcbParamAttributeStream, ParamAttribOffset * sizeof (APCB_PARAM_ATTRIBUTE));
    //Insert new attrib
    NewApcbParamData += ParamAttribOffset * sizeof (APCB_PARAM_ATTRIBUTE);
    ((APCB_PARAM_ATTRIBUTE *) NewApcbParamData)->TimePoint = APCB_TIME_POINT_ANY;
    ((APCB_PARAM_ATTRIBUTE *) NewApcbParamData)->Token = TokenId;
    ((APCB_PARAM_ATTRIBUTE *) NewApcbParamData)->Size = (*SizeInByte - 1);
    //Insert the END flag
    NewApcbParamData += sizeof (APCB_PARAM_ATTRIBUTE);
    ((APCB_PARAM_ATTRIBUTE *) NewApcbParamData)->TimePoint = 0;
    ((APCB_PARAM_ATTRIBUTE *) NewApcbParamData)->Token = APCB_TOKEN_CONFIG_LIMIT;
    ((APCB_PARAM_ATTRIBUTE *) NewApcbParamData)->Size = 0;
    ((APCB_PARAM_ATTRIBUTE *) NewApcbParamData)->Reserved = 0;
    //Copy Original value data
    NewApcbParamData += sizeof (APCB_PARAM_ATTRIBUTE);
    CopyMem (NewApcbParamData, ApcbParamValueStream, ParamValueOffset);
    //Insert new value
    NewApcbParamData += ParamValueOffset;
    CopyMem (NewApcbParamData, Value, *SizeInByte);
    //Insert End flag
    NewApcbParamData += *SizeInByte;
    *NewApcbParamData = 0xFF;
    //Now the we have the new composed APCB param type blob
    //Allocate space for hold new APCB
    ApcbShadowCopy = GetApcbShadowCopy ();
    NewApcbSize = ApcbShadowCopy->SizeOfApcb + *SizeInByte + sizeof (APCB_PARAM_ATTRIBUTE) * 2 + ALIGN_SIZE_OF_TYPE;
    NewApcb = NULL;
    NewApcb = AllocateZeroPool (NewApcbSize);
    IDS_HDT_CONSOLE_PSP_TRACE ("ALLOCATE[%x:%x]\n", NewApcb, NewApcbSize);
    ASSERT (NewApcb != NULL);
    if (NewApcb == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    //Shadow Copy pointer will be updated in below routine
    Status = ApcbReplaceType (GroupId, ApcbParamType, 0, NewApcbParamDataStart, NewApcbParamDataSize, NewApcb);
    //Free resource
    FreePool (NewApcbParamDataStart);
    IDS_HDT_CONSOLE_PSP_TRACE ("FREE[%x]\n", NewApcbParamDataStart);

    return Status;
  }
}
/**
 *
 *  Get APCB config parameters
 *  This function always get the parameters from shadow memory copy instead of read from real SPI
 *
 *  @param[in]     TokenId      APCB token ID defined in APCB_PARAM_CONFIG_TOKEN of APCB.h
 *  @param[in,out] SizeInByte   Set to non-NULL to get Size in bytes of the APCB token
 *  @param[in,out] Value        Value of APCB token ID
 *
 *  @retval EFI_SUCCESS    Get APCB value successfully
 *  @retval EFI_NOT_FOUND  Can't find the according APCB token
 *  @retval EFI_INVALID_PARAMETER  Invalid parameters
 *
 **/
EFI_STATUS
AmdPspApcbGetCfgParameter (
  IN       APCB_PARAM_CONFIG_TOKEN TokenId,
  IN OUT   UINT32          *SizeInByte,
  IN OUT   UINT64          *Value
  )
{
  EFI_STATUS Status;
  APCB_PARAM_TYPE ApcbParamType;

  IDS_HDT_CONSOLE_PSP_TRACE ("AmdPspApcbGetCfgParameter 0x%x\n", TokenId);

  //Exit service, if recovery flag set
  if (mAtRuntime == FALSE) {
    if (mApcbRecoveryFlag) {
      IDS_HDT_CONSOLE_PSP_TRACE ("APCB.RecoveryFlag Set, exit service\n");
      return EFI_UNSUPPORTED;
    }
  }

  //Exit service, if recovery flag set
  if (CheckPspRecoveryFlagV2 () == TRUE) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Recovery flag set, exit service\n");
    // ASSERT (FALSE); // Assertion in the debug build
    return EFI_UNSUPPORTED;
  }

  if ((Value == NULL) || (SizeInByte == NULL)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Input parameters error\n");
    return EFI_INVALID_PARAMETER;
  }

  //Get According APCB Group & Type ID, Check if TokenId in valid range
  if (TokenId > APCB_TOKEN_CONFIG_PSP_BEGIN && TokenId < APCB_TOKEN_CONFIG_PSP_END) {
    ApcbParamType = APCB_PSP_TYPE_CONFIG_PARAMETERS;
  } else if (TokenId > APCB_TOKEN_CONFIG_CCX_BEGIN && TokenId < APCB_TOKEN_CONFIG_CCX_END) {
    ApcbParamType = APCB_CCX_TYPE_CONFIG_PARAMETERS;
  } else if (TokenId > APCB_TOKEN_CONFIG_DF_BEGIN && TokenId < APCB_TOKEN_CONFIG_DF_END) {
    ApcbParamType = APCB_DF_TYPE_CONFIG_PARAMETERS;
  } else if (TokenId > APCB_TOKEN_CONFIG_MEM_BEGIN && TokenId < APCB_TOKEN_CONFIG_MEM_END) {
    ApcbParamType = APCB_MEM_TYPE_CONFIG_PARAMETERS;
  } else if (TokenId > APCB_TOKEN_CONFIG_GNB_BEGIN && TokenId < APCB_TOKEN_CONFIG_GNB_END) {
    ApcbParamType = APCB_GNB_TYPE_CONFIG_PARAMETERS;
  } else if (TokenId > APCB_TOKEN_CONFIG_FCH_BEGIN && TokenId < APCB_TOKEN_CONFIG_FCH_END) {
    ApcbParamType = APCB_FCH_TYPE_CONFIG_PARAMETERS;
  } else {
    IDS_HDT_CONSOLE_PSP_TRACE ("Can't find TokenId in valid APCB range\n");
    return EFI_INVALID_PARAMETER;
  }
  //Get from custom blob 1st, if not found try default blob
  Status = InternalApcbGetParameter (ApcbParamType, TokenId, SizeInByte, Value);
  if (EFI_ERROR (Status)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Can't find TokenId in custom blob, try to find in default blob\n");
    Status = InternalApcbGetParameter ((APCB_PARAM_TYPE) (ApcbParamType - 1), TokenId, SizeInByte, Value);
  }

  if (Status == EFI_SUCCESS) {
    IDS_HDT_CONSOLE_PSP_TRACE ("SizeInByte 0x%x, Value 0x%x\n", (SizeInByte != NULL) ? *SizeInByte : 0, *Value);
  }

  return Status;
}

EFI_STATUS
AmdPspApcbSetCfgParameter (
  IN       APCB_PARAM_CONFIG_TOKEN TokenId,
  IN       UINT32           *SizeInByte,
  IN       UINT64          *Value
  )
{
  EFI_STATUS Status;
  APCB_PARAM_TYPE ApcbParamType;


  IDS_HDT_CONSOLE_PSP_TRACE ("AmdPspApcbSetCfgParameter 0x%x SizeInByte 0x%x, Value 0x%x\n", TokenId, (SizeInByte != NULL) ? *SizeInByte : 0, *Value);

  //Exit service, if recovery flag set
  if (mAtRuntime == FALSE) {
    if (mApcbRecoveryFlag) {
      IDS_HDT_CONSOLE_PSP_TRACE ("APCB.RecoveryFlag Set, exit service\n");
      return EFI_UNSUPPORTED;
    }
  }
  //Exit service, if recovery flag set
  if (CheckPspRecoveryFlagV2 () == TRUE) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Recovery flag set, exit service\n");
    // ASSERT (FALSE); // Assertion in the debug build
    return EFI_UNSUPPORTED;
  }

  if ((Value == NULL) || (SizeInByte == NULL)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Input parameters error\n");
    return EFI_INVALID_PARAMETER;
  }

  //Get According APCB Group & Type ID, Check if TokenId in valid range
  if (TokenId > APCB_TOKEN_CONFIG_PSP_BEGIN && TokenId < APCB_TOKEN_CONFIG_PSP_END) {
    ApcbParamType = APCB_PSP_TYPE_CONFIG_PARAMETERS;
  } else if (TokenId > APCB_TOKEN_CONFIG_CCX_BEGIN && TokenId < APCB_TOKEN_CONFIG_CCX_END) {
    ApcbParamType = APCB_CCX_TYPE_CONFIG_PARAMETERS;
  } else if (TokenId > APCB_TOKEN_CONFIG_DF_BEGIN && TokenId < APCB_TOKEN_CONFIG_DF_END) {
    ApcbParamType = APCB_DF_TYPE_CONFIG_PARAMETERS;
  } else if (TokenId > APCB_TOKEN_CONFIG_MEM_BEGIN && TokenId < APCB_TOKEN_CONFIG_MEM_END) {
    ApcbParamType = APCB_MEM_TYPE_CONFIG_PARAMETERS;
  } else if (TokenId > APCB_TOKEN_CONFIG_GNB_BEGIN && TokenId < APCB_TOKEN_CONFIG_GNB_END) {
    ApcbParamType = APCB_GNB_TYPE_CONFIG_PARAMETERS;
  } else if (TokenId > APCB_TOKEN_CONFIG_FCH_BEGIN && TokenId < APCB_TOKEN_CONFIG_FCH_END) {
    ApcbParamType = APCB_FCH_TYPE_CONFIG_PARAMETERS;
  } else {
    IDS_HDT_CONSOLE_PSP_TRACE ("Can't find TokenId in valid APCB range\n");
    return EFI_INVALID_PARAMETER;
  }
  Status = InternalApcbSetParameter (ApcbParamType, TokenId, SizeInByte, Value);
  return Status;
}
/**
 *
 *  Get Common CBS config parameters
 *  This function always get the parameters from shadow memory copy instead of read from real SPI
 *
 *  @param[in]     TokenId      APCB token ID defined in APCB_PARAM_CONFIG_TOKEN of APCB.h
 *  @param[in,out] SizeInByte   Set to non-NULL to get Size in bytes of the APCB token
 *  @param[in,out] Value        Value of APCB token ID
 *
 *  @retval EFI_SUCCESS    Get APCB value successfully
 *  @retval EFI_NOT_FOUND  Can't find the according APCB token
 *  @retval EFI_INVALID_PARAMETER  Invalid parameters
 *
 **/
EFI_STATUS
AmdPspApcbGetCbsCmnParameter (
  IN       UINT16          TokenId,
  IN OUT   UINT32          *SizeInByte,
  IN OUT   UINT64          *Value
  )
{
  EFI_STATUS Status;
  APCB_PARAM_TYPE ApcbParamType;


  IDS_HDT_CONSOLE_PSP_TRACE ("AmdPspApcbGetCbsCmnParameter 0x%x\n", TokenId);

  //Exit service, if recovery flag set
  if (mAtRuntime == FALSE) {
    if (mApcbRecoveryFlag) {
      IDS_HDT_CONSOLE_PSP_TRACE ("APCB.RecoveryFlag Set, exit service\n");
      return EFI_UNSUPPORTED;
    }
  }
  //Exit service, if recovery flag set
  if (CheckPspRecoveryFlagV2 () == TRUE) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Recovery flag set, exit service\n");
    // ASSERT (FALSE); // Assertion in the debug build
    return EFI_UNSUPPORTED;
  }

  if ((Value == NULL) || (SizeInByte == NULL)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Input parameters error\n");
    return EFI_INVALID_PARAMETER;
  }
  //Check validity of TokenId
  if (TokenId > APCB_TOKEN_CBS_CMN_BEGIN && TokenId < APCB_TOKEN_CBS_CMN_END) {
    ApcbParamType = APCB_TYPE_CBS_COMMON_PARAMETERS;
  } else {
    IDS_HDT_CONSOLE_PSP_TRACE ("Invalid Cbs TokenId\n");
    return EFI_UNSUPPORTED;
  }
  Status = InternalApcbGetParameter (ApcbParamType, TokenId, SizeInByte, Value);
  return Status;
}

/**
 *
 *  Set Common CBS config parameters
 *  This function always get the parameters from shadow memory copy instead of read from real SPI
 *
 *  @param[in]     TokenId      APCB token ID defined in APCB_PARAM_CONFIG_TOKEN of APCB.h
 *  @param[in,out] SizeInByte   Set to non-NULL to get Size in bytes of the APCB token
 *  @param[in,out] Value        Value of APCB token ID
 *
 *  @retval EFI_SUCCESS    Get APCB value successfully
 *  @retval EFI_NOT_FOUND  Can't find the according APCB token
 *  @retval EFI_INVALID_PARAMETER  Invalid parameters
 *
 **/
EFI_STATUS
AmdPspApcbSetCbsCmnParameter (
  IN       UINT16          TokenId,
  IN OUT   UINT32          *SizeInByte,
  IN OUT   UINT64          *Value
  )
{
  EFI_STATUS Status;
  APCB_PARAM_TYPE ApcbParamType;

  IDS_HDT_CONSOLE_PSP_TRACE ("AmdPspApcbSetCbsCmnParameter 0x%x\n", TokenId);

  //Exit service, if recovery flag set
  if (mAtRuntime == FALSE) {
    if (mApcbRecoveryFlag) {
      IDS_HDT_CONSOLE_PSP_TRACE ("APCB.RecoveryFlag Set, exit service\n");
      return EFI_UNSUPPORTED;
    }
  }
  //Exit service, if recovery flag set
  if (CheckPspRecoveryFlagV2 () == TRUE) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Recovery flag set, exit service\n");
    // ASSERT (FALSE); // Assertion in the debug build
    return EFI_UNSUPPORTED;
  }

  if ((Value == NULL) || (SizeInByte == NULL)) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Input parameters error\n");
    return EFI_INVALID_PARAMETER;
  }
  IDS_HDT_CONSOLE_PSP_TRACE ("Size: 0x%x Value:0x%x\n", *SizeInByte, *Value);

  //Check validity of TokenId
  if (TokenId > APCB_TOKEN_CBS_CMN_BEGIN && TokenId < APCB_TOKEN_CBS_CMN_END) {
    ApcbParamType = APCB_TYPE_CBS_COMMON_PARAMETERS;
  } else {
    IDS_HDT_CONSOLE_PSP_TRACE ("Invalid Cbs TokenId\n");
    return EFI_UNSUPPORTED;
  }
  Status = InternalApcbSetParameter (ApcbParamType, TokenId, SizeInByte, Value);
  return Status;
}

