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
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/SmmBase2.h>
#include <Library/SmmServicesTableLib.h>

//#include "AGESA.h"
#include "Porting.h"
#include "SocLogicalId.h"
#include "Addendum/Apcb/Inc/SSP/APCB.h"
#include "ApcbCommon.h"
#include "ApcbSspSmm.h"
#include <Library/ApcbSspLib.h>
#include <Protocol/AmdApcbProtocol.h>
#include "../TokensSsp/Tokens.h"
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Filecode.h>

#define FILECODE PSP_APCB_APCBSSPSMM_APCBSSPSMM_FILECODE

extern EFI_GUID gAmdApcbSmmServiceProtocolGuid;

EFI_STATUS
DefRet (
  VOID
  )
{
  return EFI_UNSUPPORTED;
}

STATIC AMD_APCB_SERVICE_PROTOCOL mApcbSmmServiceProtocol = {
  APCB_PROTOCOL_VERSION_2_0,
  mApcbSetActiveInstance,
  mApcbFlushData,
  mApcbGetDramPostPkgRepairEntry,
  mApcbClearDramPostPkgRepairEntry,
  mApcbAddDramPostPkgRepairEntry,
  mApcbRemoveDramPostPkgRepairEntry,
  mApcbGetConfigParameter,
  mApcbSetConfigParameter,
  mApcbGetCbsParameter,
  mApcbSetCbsParameter,
  mApcbUpdateCbsData,
  (FP_ACQUIRE_MUTEX)DefRet,
  (FP_RELEASE_MUTEX)DefRet,
  (FP_GET_TOKEN_BOOL)DefRet,
  (FP_SET_TOKEN_BOOL)DefRet,
  (FP_GET_TOKEN_8)DefRet,
  (FP_SET_TOKEN_8)DefRet,
  (FP_GET_TOKEN_16)DefRet,
  (FP_SET_TOKEN_16)DefRet,
  (FP_GET_TOKEN_32)DefRet,
  (FP_SET_TOKEN_32)DefRet,
  (FP_GET_TYPE)DefRet,
  (FP_SET_TYPE)DefRet,
  (FP_PURGE_ALL_TOKENS)DefRet,
  (FP_PURGE_ALL_TYPES)DefRet
};

UINT8                     mActiveApcbInstance = 0;


/*++

Routine Description:

  This function sets the active APCB instance
  TODO: Not needed for now. Reserved for future compatibility

--*/
VOID
mApcbSetActiveInstance (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8             Instance
  )
{
  mActiveApcbInstance = Instance;
}

BOOLEAN
mApcbCheckInstance (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This
  )
{
  if (mActiveApcbInstance == 0xFF) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Error: Uninitialized active APCB instance\n");
    return FALSE;
  }

  return TRUE;
}

/*++

Routine Description:

  This function flush the APCB data back to SPI ROM

--*/
EFI_STATUS
mApcbFlushData (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This
  )
{
  // Write back Shadow Copy in DRAM
  IDS_HDT_CONSOLE_PSP_TRACE ("Write back APCB to SPI\n");
  return AmdPspWriteBackApcbShadowCopy ();
}

/*++

Routine Description:

  This function udpates the APCB data for CBS backend

--*/
EFI_STATUS
mApcbUpdateCbsData (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT8             *ApcbTypeData,
  IN       UINT32            SizeInByte,
  IN       BOOLEAN           Internal
  )
{
  EFI_STATUS                Status;
  UINT16                    Type;
  APCB_HEADER               *ApcbShadowCopy;
  UINT8                     *NewApcb;
  UINT32                    NewApcbSize;

  if (!mApcbCheckInstance (This)) {
    return EFI_INVALID_PARAMETER;
  }

  Type = Internal ? APCB_TYPE_CBS_DEBUG_PARAMETERS : APCB_TYPE_CBS_COMMON_PARAMETERS;
  ApcbShadowCopy = GetApcbShadowCopy ();
  NewApcbSize = ApcbShadowCopy->SizeOfApcb + SizeInByte + sizeof (APCB_PARAM_ATTRIBUTE) * 2 + ALIGN_SIZE_OF_TYPE;
  NewApcb = NULL;
  NewApcb = AllocateZeroPool (NewApcbSize);

  Status = ApcbReplaceType (APCB_GROUP_CBS, Type, 0, ApcbTypeData, SizeInByte, NewApcb);
  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
    return Status;
  }

  // Write back Shadow Copy in DRAM
  IDS_HDT_CONSOLE_PSP_TRACE ("Write back APCB to SPI\n");
  AmdPspWriteBackApcbShadowCopy ();

  return EFI_SUCCESS;
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
 *  @retval EFI_NOT_FOUND  Can't find the according APCB token
 *  @retval EFI_INVALID_PARAMETER  Invalid parameters
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
  if (!mApcbCheckInstance (This)) {
    return EFI_INVALID_PARAMETER;
  }

  return AmdPspApcbGetCfgParameter (mTranslateConfigTokenId(TokenId), SizeInByte, Value);
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
 *  @retval EFI_NOT_FOUND  Can't find the according APCB token
 *  @retval EFI_INVALID_PARAMETER  Invalid parameters
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
  if (!mApcbCheckInstance (This)) {
    return EFI_INVALID_PARAMETER;
  }

  return AmdPspApcbSetCfgParameter (mTranslateConfigTokenId(TokenId), SizeInByte, Value);
}

/**
 *
 * Routine Description:
 *
 *   This function gets the APCB CBS parameter
 *
 *  @param[in]     TokenId      APCB token ID defined in APCB_COMMON_CBS_EXT_ID of ApcbCommon.h
 *  @param[in,out] SizeInByte   Set to non-NULL to get Size in bytes of the APCB token
 *  @param[in,out] Value        Value of APCB token ID
 *
 *  @retval EFI_SUCCESS    Get APCB value successfully
 *  @retval EFI_NOT_FOUND  Can't find the according APCB token
 *  @retval EFI_INVALID_PARAMETER  Invalid parameters
 *
 **/
EFI_STATUS
mApcbGetCbsParameter (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT16            TokenId,
  IN OUT   UINT32            *SizeInByte,
  IN OUT   UINT64            *Value
  )
{
  if (!mApcbCheckInstance (This)) {
    return EFI_INVALID_PARAMETER;
  }

  return AmdPspApcbGetCbsCmnParameter (mTranslateCbsExtTokenId(TokenId), SizeInByte, Value);
}

/**
 *
 * Routine Description:
 *
 *   This function sets the APCB CBS parameter
 *
 *  @param[in]     TokenId      APCB token ID defined in APCB_COMMON_CBS_EXT_ID of ApcbCommon.h
 *  @param[in,out] SizeInByte   Set to non-NULL to get Size in bytes of the APCB token
 *  @param[in,out] Value        Value of APCB token ID
 *
 *  @retval EFI_SUCCESS    Set APCB value successfully
 *  @retval EFI_NOT_FOUND  Can't find the according APCB token
 *  @retval EFI_INVALID_PARAMETER  Invalid parameters
 *
 **/
EFI_STATUS
mApcbSetCbsParameter (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       UINT16            TokenId,
  IN OUT   UINT32            *SizeInByte,
  IN OUT   UINT64            *Value
  )
{
  if (!mApcbCheckInstance (This)) {
    return EFI_INVALID_PARAMETER;
  }

  return AmdPspApcbSetCbsCmnParameter (mTranslateCbsExtTokenId(TokenId), SizeInByte, Value);
}

/**
 *
 * Routine Description:
 *
 *   This function retrieves the DRAM POST Package repair entries
 *
 *  @param[in, out] Entry      pointer to the DRAM POST Package repair entries to be retrieved
 *
 *  @param[in, out] NumOfEntries  Number of DRAM POST Package repair entries to be returned
 *
 *  @retval EFI_SUCCESS    DRAM POST Package repair entries cleared successfully
 *
 **/
EFI_STATUS
mApcbGetDramPostPkgRepairEntry (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN OUT   DRRP_REPAIR_ENTRY *Entry,
  IN OUT   UINT32            *NumOfEntries
  )
{
  EFI_STATUS                Status;
  UINT8                     i;
  APCB_DPPRCL_REPAIR_ENTRY  *RepairEntry;
  UINT32                    SizeInByte;

  if (!mApcbCheckInstance (This)) {
    return EFI_INVALID_PARAMETER;
  }

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
  }

  return Status;
}

/**
 *
 * Routine Description:
 *
 *   This function clears the DRAM POST Package repair entries
 *
 *  @retval EFI_SUCCESS    DRAM POST Package repair entries cleared successfully
 *
 **/
EFI_STATUS
mApcbClearDramPostPkgRepairEntry (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This
  )
{
  if (!mApcbCheckInstance (This)) {
    return EFI_INVALID_PARAMETER;
  }

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
 *  @retval EFI_SUCCESS    DRAM POST Package repair entry added successfully
 *
 **/
EFI_STATUS
mApcbAddDramPostPkgRepairEntry (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       DRRP_REPAIR_ENTRY *Entry
  )
{
  APCB_DPPRCL_REPAIR_ENTRY  RepairEntry;

  if (!mApcbCheckInstance (This)) {
    return EFI_INVALID_PARAMETER;
  }

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
 *  @retval EFI_SUCCESS    DRAM POST Package repair entry removed successfully
 *
 **/
EFI_STATUS
mApcbRemoveDramPostPkgRepairEntry (
  IN       AMD_APCB_SERVICE_PROTOCOL    *This,
  IN       DRRP_REPAIR_ENTRY *Entry
  )
{
  APCB_DPPRCL_REPAIR_ENTRY  RepairEntry;

  if (!mApcbCheckInstance (This)) {
    return EFI_INVALID_PARAMETER;
  }

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

  return ApcbRemoveDramPostPkgRepairEntry (&RepairEntry);
}


EFI_STATUS
AmdApcbSspSmmDriverEntry (
  IN       EFI_HANDLE         ImageHandle,
  IN       EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                  Status;
  EFI_HANDLE                  Handle;

  AGESA_TESTPOINT (TpApcbSmmEntry, NULL);
  IDS_HDT_CONSOLE_PSP_TRACE ("APCB SMM Driver Entry\n");
  Handle = NULL;
  //Install APCB service Protocol
  Status = gSmst->SmmInstallProtocolInterface (
               &Handle,
               &gAmdApcbSmmServiceProtocolGuid,
               EFI_NATIVE_INTERFACE,
               &mApcbSmmServiceProtocol
               );
  if (EFI_ERROR (Status)) {
    ASSERT (FALSE);
  }

  IDS_HDT_CONSOLE_PSP_TRACE ("APCB SMM Driver Exit\n");
  AGESA_TESTPOINT (TpApcbSmmExit, NULL);
  return EFI_SUCCESS;
}

