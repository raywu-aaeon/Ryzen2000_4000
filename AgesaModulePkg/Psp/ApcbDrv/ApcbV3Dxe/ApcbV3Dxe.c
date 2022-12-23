/* $NoKeywords:$ */
/**
 * @file
 *
 * APCB DXE Driver
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  APCB
 * @e \$Revision$   @e \$Date$
 *
 */
/*****************************************************************************
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
#include <PiDxe.h>
#include <Guid/EventGroup.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

//#include "AGESA.h"
#include "Porting.h"
#include "SocLogicalId.h"
#include "Addendum/Apcb/Inc/SSP/APCB.h"
#include "ApcbV3Dxe.h"
#include <Library/ApcbLibV3.h>
#include <Protocol/AmdApcbProtocol.h>
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Filecode.h>

#define FILECODE PSP_APCB_APCBV3DXE_APCBV3DXE_FILECODE

extern EFI_GUID gAmdApcbDxeServiceProtocolGuid;

EFI_STATUS
DefRet (
  VOID
  )
{
  return EFI_UNSUPPORTED;
}

STATIC AMD_APCB_SERVICE_PROTOCOL mApcbDxeServiceProtocol = {
  APCB_PROTOCOL_VERSION_3_0,
  (FP_SET_ACTIVE_APCB_INSTANCE)DefRet,
  mApcbFlushData,
  mApcbGetDramPostPkgRepairEntry,
  mApcbClearDramPostPkgRepairEntry,
  mApcbAddDramPostPkgRepairEntry,
  mApcbRemoveDramPostPkgRepairEntry,
  mApcbGetConfigParameter,
  mApcbSetConfigParameter,
  (FP_GET_CBS_PARAM)DefRet,
  (FP_SET_CBS_PARAM)DefRet,
  (FP_UPDATE_CBS_APCB_DATA)DefRet,
  mApcbAcquireMutex,
  mApcbReleaseMutex,
  mApcbGetTokenBool,
  mApcbSetTokenBool,
  mApcbGetToken8,
  mApcbSetToken8,
  mApcbGetToken16,
  mApcbSetToken16,
  mApcbGetToken32,
  mApcbSetToken32,
  mApcbGetType,
  mApcbSetType,
  mApcbPurgeAllTokens,
  mApcbPurgeAllTypes
};




/*++

Routine Description:

 *  This function flush the APCB data back to SPI ROM
 *
 *  @param[in]     PriorityLevel      APCB priority level of the current operation
 *
--*/
EFI_STATUS
mApcbFlushData (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This
  )
{
  //
  // Write back Shadow Copy in DRAM
  //
  IDS_HDT_CONSOLE_PSP_TRACE ("Write back APCB to SPI\n");
  return AmdPspWriteBackApcbShadowCopy ();
}

/**
 *
 * Routine Description:
 *
 *   This function gets the APCB config parameter
 *
 *  @param[in]     TokenId      APCB token ID defined in APCB_COMMON_CONFIG_ID of ApcbCommon.h
 *  @param[in,out] SizeInByte   Set to non-NULL to get Size in bytes of the APCB token
 *  @param[in,out] Value        Value of APCB token ID
 *
 *  @retval EFI_SUCCESS    Get APCB value successfully
 *          EFI_NOT_FOUND  Can't find the according APCB token
 *          EFI_INVALID_PARAMETER  Invalid parameters
 *
 **/
EFI_STATUS
mApcbGetConfigParameter (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT16            TokenId,
  IN OUT   UINT32            *SizeInByte,
  IN OUT   UINT64            *Value
  )
{
  if (ApcbV2GetConfigToken (TokenId, SizeInByte, Value)) {
    return EFI_SUCCESS;
  } else {
    return EFI_NOT_FOUND;
  }
}

/**
 *
 * Routine Description:
 *
 *   This function sets the APCB config parameter
 *
 *  @param[in]     TokenId      APCB token ID defined in APCB_COMMON_CONFIG_ID of ApcbCommon.h
 *  @param[in,out] SizeInByte   Set to non-NULL to get Size in bytes of the APCB token
 *  @param[in,out] Value        Value of APCB token ID
 *
 *  @retval EFI_SUCCESS    Set APCB value successfully
 *          EFI_NOT_FOUND  Can't find the according APCB token
 *          EFI_INVALID_PARAMETER  Invalid parameters
 *
 **/
EFI_STATUS
mApcbSetConfigParameter (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT16            TokenId,
  IN OUT   UINT32            *SizeInByte,
  IN OUT   UINT64            *Value
  )
{
  if (ApcbV2SetConfigToken (TokenId, SizeInByte, Value)) {
    return EFI_SUCCESS;
  } else {
    return EFI_NOT_FOUND;
  }
}

/**
 *
 * Routine Description:
 *
 *  This function acquires the Mutex for subsequent APCB operations
 *
 *  @retval EFI_ACCESS_DENIED  APCB cannot be accessed
 *
 **/
EFI_STATUS
mApcbAcquireMutex (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This
  )
{
  if (ApcbAcquireMutex ()) {
    return EFI_SUCCESS;      
  }

  return EFI_ACCESS_DENIED;
}

/**
 *
 * Routine Description:
 *
 * This function releases the Mutex for previous APCB operations
 *
 *
 **/
EFI_STATUS
mApcbReleaseMutex (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This
  )
{
  ApcbReleaseMutex ();

  return EFI_SUCCESS;
}

/**
 *
 * Routine Description:
 *
 *   This function gets an Boolean APCB token value
 *
 *  @param[in]          This               Pointer to the instance of APCB Protocol
 *  @param[out]         Purpose            Purpose of the APCB type where the data is retrieved
 *  @param[in]          Uid                APCB token UID defined in ApcbV3TokenUid.h
 *  @param[out]         bValue             Value of APCB token ID
 *
 *  @retval EFI_SUCCESS    Get APCB value successfully
 *          EFI_NOT_FOUND  Can't find the APCB token
 *
 **/
EFI_STATUS
mApcbGetTokenBool (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
     OUT   UINT8                        *Purpose,
  IN       UINT32            Uid,
     OUT   BOOLEAN           *bValue
  )
{
  UINT8 CurrentPriorityLevel;
  UINT8 StartingPriorityLevel;
  UINT8 EndingPriorityLevel;

  StartingPriorityLevel = APCB_PRIORITY_LEVEL_HARD_FORCE;
  EndingPriorityLevel = APCB_PRIORITY_LEVEL_LIMIT;

  for (CurrentPriorityLevel = StartingPriorityLevel; CurrentPriorityLevel < EndingPriorityLevel; CurrentPriorityLevel ++) {
    ApcbSetPriorityLevel (CurrentPriorityLevel);
    if (ApcbGetBool (Uid, bValue)) {
      if (NULL != Purpose) {
        *Purpose = ApcbGetPurpose ();
      }
      return EFI_SUCCESS;
    }
  }
  return EFI_NOT_FOUND;
}

/**
 *
 * Routine Description:
 *
 *   This function sets an Boolean APCB token value
 *
 *  @param[in]     This               Pointer to the instance of APCB Protocol
 *  @param[in]     Purpose            Purpose of the current operation
 *  @param[in]     Uid                APCB token UID defined in ApcbV3TokenUid.h
 *  @param[in]     bValue             Value of APCB token ID
 *
 *  @retval EFI_SUCCESS           Set APCB value successfully
 *          EFI_OUT_OF_RESOURCES  Can't set the APCB token
 *
 **/
EFI_STATUS
mApcbSetTokenBool (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8                        Purpose,
  IN       UINT32            Uid,
  IN       BOOLEAN           bValue
  )
{
  ApcbSetPurpose (Purpose);
  if (ApcbSetBool (Uid, bValue)) {
    return EFI_SUCCESS;
  } else {
    return EFI_OUT_OF_RESOURCES;
  }
}

/**
 *
 * Routine Description:
 *
 *   This function gets an UINT8 APCB token value
 *
 *  @param[in]          This               Pointer to the instance of APCB Protocol
 *  @param[out]         Purpose            Purpose of the APCB type where the data is retrieved
 *  @param[in]          Uid                APCB token UID defined in ApcbV3TokenUid.h
 *  @param[out]         Value8             Value of APCB token ID
 *
 *  @retval EFI_SUCCESS    Get APCB value successfully
 *          EFI_NOT_FOUND  Can't find the APCB token
 *
 **/
EFI_STATUS
mApcbGetToken8 (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
     OUT   UINT8                        *Purpose,
  IN       UINT32            Uid,
     OUT   UINT8             *Value8
  )
{
  UINT8 CurrentPriorityLevel;
  UINT8 StartingPriorityLevel;
  UINT8 EndingPriorityLevel;

  StartingPriorityLevel = APCB_PRIORITY_LEVEL_HARD_FORCE;
  EndingPriorityLevel = APCB_PRIORITY_LEVEL_LIMIT;

  for (CurrentPriorityLevel = StartingPriorityLevel; CurrentPriorityLevel < EndingPriorityLevel; CurrentPriorityLevel ++) {
    ApcbSetPriorityLevel (CurrentPriorityLevel);
    if (ApcbGet8 (Uid, Value8)) {
      if (NULL != Purpose) {
        *Purpose = ApcbGetPurpose ();
      }
      return EFI_SUCCESS;
    }
  }
  return EFI_NOT_FOUND;
}

/**
 *
 * Routine Description:
 *
 *   This function sets an UINT8 APCB token value
 *
 *  @param[in]     This               Pointer to the instance of APCB Protocol
 *  @param[in]     Purpose            Purpose of the current operation
 *  @param[in]     Uid                APCB token UID defined in ApcbV3TokenUid.h
 *  @param[in]     Value8             Value of APCB token ID
 *
 *  @retval EFI_SUCCESS           Set APCB value successfully
 *          EFI_OUT_OF_RESOURCES  Can't set the APCB token
 *
 **/
EFI_STATUS
mApcbSetToken8 (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8                        Purpose,
  IN       UINT32            Uid,
  IN       UINT8             Value8
  )
{
  ApcbSetPurpose (Purpose);
  if (ApcbSet8 (Uid, Value8)) {
    return EFI_SUCCESS;
  } else {
    return EFI_OUT_OF_RESOURCES;
  }
}

/**
 *
 * Routine Description:
 *
 *   This function gets an UINT16 APCB token value
 *
 *  @param[in]          This               Pointer to the instance of APCB Protocol
 *  @param[out]         Purpose            Purpose of the APCB type where the data is retrieved
 *  @param[in]          Uid                APCB token UID defined in ApcbV3TokenUid.h
 *  @param[out]         bValue             Value of APCB token ID
 *
 *  @retval EFI_SUCCESS    Get APCB value successfully
 *          EFI_NOT_FOUND  Can't find the APCB token
 *
 **/
EFI_STATUS
mApcbGetToken16 (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
     OUT   UINT8                        *Purpose,
  IN       UINT32            Uid,
     OUT   UINT16            *Value16
  )
{
  UINT8 CurrentPriorityLevel;
  UINT8 StartingPriorityLevel;
  UINT8 EndingPriorityLevel;

  StartingPriorityLevel = APCB_PRIORITY_LEVEL_HARD_FORCE;
  EndingPriorityLevel = APCB_PRIORITY_LEVEL_LIMIT;

  for (CurrentPriorityLevel = StartingPriorityLevel; CurrentPriorityLevel < EndingPriorityLevel; CurrentPriorityLevel ++) {
    ApcbSetPriorityLevel (CurrentPriorityLevel);
    if (ApcbGet16 (Uid, Value16)) {
      if (NULL != Purpose) {
        *Purpose = ApcbGetPurpose ();
      }
      return EFI_SUCCESS;
    }
  }
  return EFI_NOT_FOUND;
}

/**
 *
 * Routine Description:
 *
 *   This function sets an UINT16 APCB token value
 *
 *  @param[in]     This               Pointer to the instance of APCB Protocol
 *  @param[in]     Purpose            Purpose of the current operation
 *  @param[in]     Uid                APCB token UID defined in ApcbV3TokenUid.h
 *  @param[in]     Value16            Value of APCB token ID
 *
 *  @retval EFI_SUCCESS           Set APCB value successfully
 *          EFI_OUT_OF_RESOURCES  Can't set the APCB token
 *
 **/
EFI_STATUS
mApcbSetToken16 (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8                        Purpose,
  IN       UINT32            Uid,
  IN       UINT16            Value16
  )
{
  ApcbSetPurpose (Purpose);
  if (ApcbSet16 (Uid, Value16)) {
    return EFI_SUCCESS;
  } else {
    return EFI_OUT_OF_RESOURCES;
  }
}

/**
 *
 * Routine Description:
 *
 *   This function gets an UINT32 APCB token value
 *
 *  @param[in]          This               Pointer to the instance of APCB Protocol
 *  @param[out]         Purpose            Purpose of the APCB type where the data is retrieved
 *  @param[in]          Uid                APCB token UID defined in ApcbV3TokenUid.h
 *  @param[out]         bValue             Value of APCB token ID
 *
 *  @retval EFI_SUCCESS    Get APCB value successfully
 *          EFI_NOT_FOUND  Can't find the APCB token
 *
 **/
EFI_STATUS
mApcbGetToken32 (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
     OUT   UINT8                        *Purpose,
  IN       UINT32            Uid,
     OUT   UINT32            *Value32
  )
{
  UINT8 CurrentPriorityLevel;
  UINT8 StartingPriorityLevel;
  UINT8 EndingPriorityLevel;

  StartingPriorityLevel = APCB_PRIORITY_LEVEL_HARD_FORCE;
  EndingPriorityLevel = APCB_PRIORITY_LEVEL_LIMIT;

  for (CurrentPriorityLevel = StartingPriorityLevel; CurrentPriorityLevel < EndingPriorityLevel; CurrentPriorityLevel ++) {
    ApcbSetPriorityLevel (CurrentPriorityLevel);
    if (ApcbGet32 (Uid, Value32)) {
      if (NULL != Purpose) {
        *Purpose = ApcbGetPurpose ();
      }
      return EFI_SUCCESS;
    }
  }
  return EFI_NOT_FOUND;
}

/**
 *
 * Routine Description:
 *
 *   This function sets an UINT32 APCB token value
 *
 *  @param[in]     This               Pointer to the instance of APCB Protocol
 *  @param[in]     Purpose            Purpose of the current operation
 *  @param[in]     Uid                APCB token UID defined in ApcbV3TokenUid.h
 *  @param[in]     Value32            Value of APCB token ID
 *
 *  @retval EFI_SUCCESS           Set APCB value successfully
 *          EFI_OUT_OF_RESOURCES  Can't set the APCB token
 *
 **/
EFI_STATUS
mApcbSetToken32 (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8                        Purpose,
  IN       UINT32            Uid,
  IN       UINT32            Value32
  )
{
  ApcbSetPurpose (Purpose);
  if (ApcbSet32 (Uid, Value32)) {
    return EFI_SUCCESS;
  } else {
    return EFI_OUT_OF_RESOURCES;
  }
}

/**
 *  This function retrieves the data of a specified type
 *
 *  @param[in]          This               Pointer to the instance of APCB Protocol
 *  @param[out]         Purpose            Purpose of the APCB type where the data is retrieved
 *  @param[in]          GroupId            Group ID
 *  @param[in]          TypeId             Type ID
 *  @param[out]         DataBuf            Pointer to the type data
 *  @param[out]         DataSize           Pointer to the size of the type data
 *
 * @retval        EFI_SUCCESS        The type data is retrieved successfully
 *                EFI_NOT_FOUND      The type data cannot be retrieved
 *
 **/
EFI_STATUS
mApcbGetType (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
      OUT  UINT8                        *Purpose,
  IN       UINT16        GroupId,
  IN       UINT16        TypeId,
      OUT  UINT8         **DataBuf,
      OUT  UINT32        *DataSize
  )
{
  UINT8 CurrentPriorityLevel;
  UINT8 StartingPriorityLevel;
  UINT8 EndingPriorityLevel;

  StartingPriorityLevel = APCB_PRIORITY_LEVEL_HARD_FORCE;
  EndingPriorityLevel = APCB_PRIORITY_LEVEL_LIMIT;

  for (CurrentPriorityLevel = StartingPriorityLevel; CurrentPriorityLevel < EndingPriorityLevel; CurrentPriorityLevel ++) {
    ApcbSetPriorityLevel (CurrentPriorityLevel);
    if (ApcbGetType (GroupId, TypeId, DataBuf, DataSize)) {
      if (NULL != Purpose) {
        *Purpose = ApcbGetPurpose ();
      }
      return EFI_SUCCESS;
    }
  }
  return EFI_NOT_FOUND;
}

/**
 *  This function sets the data of a specified type
 *
 * @param[in]     This               Pointer to the instance of APCB Protocol
 * @param[in]     Purpose            Purpose of the current operation
 * @param[in]     GroupId            Group ID
 * @param[in]     TypeId             Type ID
 * @param[in]     DataBuf            Pointer to the type data
 * @param[in]     DataSize           Pointer to the size of the type data
 *
 * @retval        EFI_SUCCESS        The type data is set successfully
 *                EFI_NOT_FOUND      The type data cannot be retrieved
 *
 **/
EFI_STATUS
mApcbSetType (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8                        Purpose,
  IN       UINT16        GroupId,
  IN       UINT16        TypeId,
  IN       UINT8         *DataBuf,
  IN       UINT32        DataSize
  )
{
  ApcbSetPurpose (Purpose);
  if (ApcbSetType (GroupId, TypeId, DataBuf, DataSize)) {
    return EFI_SUCCESS;
  } else {
    return EFI_NOT_FOUND;
  }
}

/**
 *
 * Routine Description:
 *
 *   This function purges all the APCB tokens
 *
 *  @param[in]     This               Pointer to the instance of APCB Protocol
 *  @param[in]     Purpose            Purpose of the current operation
 *
 *  @retval EFI_SUCCESS           All tokens are purged
 *          EFI_NOT_FOUND         All tokens are not purged
 *
 **/
EFI_STATUS
mApcbPurgeAllTokens (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8                        Purpose
  )
{
  ApcbSetPurpose (Purpose);
  if (ApcbPurgeAllTokens ()) {
    return EFI_SUCCESS;
  } else {
    return EFI_NOT_FOUND;
  }
}

/**
 *
 * Routine Description:
 *
 *   This function purges the data of all types
 *
 *  @param[in]     This               Pointer to the instance of APCB Protocol
 *  @param[in]     Purpose            Purpose of the current operation
 *
 *  @retval EFI_SUCCESS                  All types are purged
 *          EFI_OUT_OF_RESOURCES         All types are not purged
 *
 **/
EFI_STATUS
mApcbPurgeAllTypes (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8                        Purpose
  )
{
  ApcbSetPurpose (Purpose);
  if (ApcbPurgeAllTypes ()) {
    return EFI_SUCCESS;
  } else {
    return EFI_OUT_OF_RESOURCES;
  }
}

/**
 *
 * Routine Description:
 *
 *   This function retrieves the DRAM POST Package repair entries
 *
 *  @param[in, out]     Entry             pointer to the DRAM POST Package repair entries to be retrieved
 *  @param[in, out]     NumOfEntries      Number of DRAM POST Package repair entries to be returned
 *
 *  @retval EFI_SUCCESS        DRAM POST Package repair entries cleared successfully
 *
 **/
EFI_STATUS
mApcbGetDramPostPkgRepairEntry (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN OUT   DRRP_REPAIR_ENTRY            *Entry,
  IN OUT   UINT32                       *NumOfEntries
  )
{
  EFI_STATUS                Status;
  UINT8                     i;
  APCB_DPPRCL_REPAIR_ENTRY  *RepairEntry;
  UINT32                    SizeInByte;
  UINT8                     CurrentPriorityLevel;
  UINT8                     StartingPriorityLevel;
  UINT8                     EndingPriorityLevel;

  StartingPriorityLevel = APCB_PRIORITY_LEVEL_HARD_FORCE;
  EndingPriorityLevel = APCB_PRIORITY_LEVEL_LIMIT;

  for (CurrentPriorityLevel = StartingPriorityLevel; CurrentPriorityLevel < EndingPriorityLevel; CurrentPriorityLevel ++) {
    ApcbSetPriorityLevel (CurrentPriorityLevel);
    Status = ApcbGetDramPostPkgRepairEntries (&RepairEntry, &SizeInByte);
    if (EFI_SUCCESS == Status) {
      if (NumOfEntries != NULL) {
        *NumOfEntries = SizeInByte / sizeof (APCB_DPPRCL_REPAIR_ENTRY);
      } else {
        return EFI_INVALID_PARAMETER;
      }

      if (Entry != NULL) {
        for (i = 0; i < *NumOfEntries; i ++, Entry ++, RepairEntry ++) {
          Entry->Valid             = RepairEntry->Valid;
          Entry->Bank              = RepairEntry->Bank;
          Entry->RankMultiplier    = RepairEntry->RankMultiplier;
          Entry->Device            = RepairEntry->Device;
          Entry->ChipSelect        = RepairEntry->ChipSelect;
          Entry->Column            = RepairEntry->Column;
          Entry->RepairType        = RepairEntry->RepairType;
          Entry->Row               = RepairEntry->Row;
          Entry->Socket            = RepairEntry->Socket;
          Entry->Channel           = RepairEntry->Channel;
        }
      }
      return Status;
    }
  }

  return EFI_NOT_FOUND;
}

/**
 *
 * Routine Description:
 *
 *   This function clears the DRAM POST Package repair entries
 *
 *  @retval EFI_SUCCESS        DRAM POST Package repair entries cleared successfully
 *
 **/
EFI_STATUS
mApcbClearDramPostPkgRepairEntry (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This
  )
{
  ApcbSetPurpose (APCB_TYPE_PURPOSE_EVENT_LOGGING);
  return ApcbClearDramPostPkgRepairEntry ();
}

/**
 *
 * Routine Description:
 *
 *   This function adds a DRAM POST Package repair entry
 *
 *  @param[in]     Entry      DRAM POST Package repair entry to be added
 *
 *  @retval EFI_SUCCESS        DRAM POST Package repair entry added successfully
 *
 **/
EFI_STATUS
mApcbAddDramPostPkgRepairEntry (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       DRRP_REPAIR_ENTRY *Entry
  )
{
  APCB_DPPRCL_REPAIR_ENTRY  RepairEntry;

  RepairEntry.Valid         = 1;
  RepairEntry.Bank          = Entry->Bank;
  RepairEntry.RankMultiplier= Entry->RankMultiplier;
  RepairEntry.Device        = Entry->Device;
  RepairEntry.ChipSelect    = Entry->ChipSelect;
  RepairEntry.Column        = Entry->Column;
  RepairEntry.RepairType    = Entry->RepairType;
  RepairEntry.Row           = Entry->Row;
  RepairEntry.Socket        = Entry->Socket;
  RepairEntry.Channel       = Entry->Channel;

  ApcbSetPurpose (APCB_TYPE_PURPOSE_EVENT_LOGGING);
  return ApcbAddDramPostPkgRepairEntry (&RepairEntry);
}

/**
 *
 * Routine Description:
 *
 *  This function removes a DRAM POST Package repair entry
 *
 *  @param[in]     Entry      DRAM POST Package repair entry to be removed
 *
 *  @retval EFI_SUCCESS        DRAM POST Package repair entry removed successfully
 *
 **/
EFI_STATUS
mApcbRemoveDramPostPkgRepairEntry (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       DRRP_REPAIR_ENTRY *Entry
  )
{
  APCB_DPPRCL_REPAIR_ENTRY  RepairEntry;

  RepairEntry.Valid         = 1;
  RepairEntry.Bank          = Entry->Bank;
  RepairEntry.RankMultiplier= Entry->RankMultiplier;
  RepairEntry.Device        = Entry->Device;
  RepairEntry.ChipSelect    = Entry->ChipSelect;
  RepairEntry.Column        = Entry->Column;
  RepairEntry.RepairType    = Entry->RepairType;
  RepairEntry.Row           = Entry->Row;
  RepairEntry.Socket        = Entry->Socket;
  RepairEntry.Channel       = Entry->Channel;

  ApcbSetPurpose (APCB_TYPE_PURPOSE_EVENT_LOGGING);
  return ApcbRemoveDramPostPkgRepairEntry (&RepairEntry);
}

EFI_STATUS
AmdApcbV3DxeDriverEntry (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                  Status;
  EFI_HANDLE                  Handle;

  AGESA_TESTPOINT (TpApcbDxeEntry, NULL);
  IDS_HDT_CONSOLE_PSP_TRACE ("APCB V3 DXE Driver Entry\n");
  Handle = NULL;
  //Install APCB service Protocol
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gAmdApcbDxeServiceProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mApcbDxeServiceProtocol
                  );
  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("APCB V3 DXE Driver Exit\n");
  AGESA_TESTPOINT (TpApcbDxeExit, NULL);
  return EFI_SUCCESS;
}

