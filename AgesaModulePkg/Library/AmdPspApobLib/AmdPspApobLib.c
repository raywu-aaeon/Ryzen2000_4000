/* $NoKeywords:$ */
/**
 * @file
 *
 * PSP APOB related functions
 *
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  PSP
 * @e \$Revision: 309172 $   @e \$Date: 2014-12-10 21:13:24 +0800 (Wed, 10 Dec 2014) $
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
 **/
#include "Uefi.h"
#include <Pi/PiMultiPhase.h>
#include "AGESA.h"
#include <Library/AmdBaseLib.h>
#include <Library/IdsLib.h>
#include <Library/AmdSocBaseLib.h>
#include <Library/AmdPspBaseLibV2.h>
#include <Library/AmdPspMboxLibV2.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/AmdPspApobLib.h>
#include <Library/FchBaseLib.h>
#include <Library/AmdCapsuleLib.h>
#include <Addendum/Apcb/Inc/APOBCMN.h>
#include <Filecode.h>

#define FILECODE LIBRARY_AMDPSPAPOBLIB_AMDPSPAPOBLIB_FILECODE

extern EFI_GUID gAmdPspApobHobGuid;


/**
 *  Get APOBLib Info Data
 *
 * @param[in,out]  **ApobInfo      Pointer to fill the APOB Info
 *
 *  @retval EFI_SUCCESS       The APOB pointer get successfully
 *
 **/
EFI_STATUS
AmdPspGetApobInfo (
  IN OUT   APOBLIB_INFO  **ApobInfo
  )
{
  EFI_HOB_GUID_TYPE                 *GuidHob;

  ASSERT (ApobInfo != NULL);
  if (ApobInfo == NULL) {
    return EFI_UNSUPPORTED;
  }

  *ApobInfo = NULL;
  GuidHob = GetFirstGuidHob (&gAmdPspApobHobGuid);

  if (GuidHob == NULL) {
    return EFI_UNSUPPORTED;
  }

  *ApobInfo = (APOBLIB_INFO *) GET_GUID_HOB_DATA (GuidHob);

  return EFI_SUCCESS;
}
/**
 *  Return Array of Entry instance as specified GroupId, DataTypeId
 *
 *  @param[in] GroupID GroupId of Apob entry
 *  @param[in] DataTypeID DataTypeID of Apob entry
 *  @param[in] ReadFromSpiCopy TRUE force read from SPI copy
 *  @param[out] NumofEntry Number of entry found of specific GroupId, DataTypeId
 *  @param[out] ApobEntries Point to the arrary which used to hold the ApobEntries
 *              ApobEntries arrary need be allocated outside of the routine
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
AmdPspGetApobEntry (
  IN       UINT32  GroupID,
  IN       UINT32  DataTypeID,
  IN       BOOLEAN  ReadFromSpiCopy,
     OUT   UINT32  *NumofEntry,
     OUT   APOB_TYPE_HEADER **ApobEntries
  )
{
  UINT8 *ApobEntryBin;
  APOB_TYPE_HEADER *ApobEntry;
  UINT32 _NumofEntry;
  APOB_BASE_HEADER *ApobHeaderPtr;
  APOBLIB_INFO *ApobInfoPtr;
  EFI_STATUS Status;
  TYPE_ATTRIB       TypeAttrib;
  UINT64            EntryAddress;
  UINT32            EntrySize;
  UINT64            EntryDest;

  *NumofEntry = 0;
  *ApobEntries = NULL;
  ApobEntryBin = NULL;
  IDS_HDT_CONSOLE_PSP_TRACE ("AmdPspGetApobEntry %x %x\n", GroupID, DataTypeID);


  if (ReadFromSpiCopy) {
    if (BIOSEntryInfo (APOB_NV_COPY, INSTANCE_IGNORED, &TypeAttrib, &EntryAddress, &EntrySize, &EntryDest) == FALSE) {
      IDS_HDT_CONSOLE_PSP_TRACE ("APOB NV Entry not found\n");
      return EFI_NOT_FOUND;
    }
    ApobHeaderPtr = (APOB_BASE_HEADER *) (UINTN) EntryAddress;
  } else {
    Status = AmdPspGetApobInfo (&ApobInfoPtr);
    if (EFI_ERROR (Status)) {
      IDS_HDT_CONSOLE_PSP_TRACE ("APOBLIB Info data uninitialized\n");
      return Status;
    }

    if (ApobInfoPtr->Supported == FALSE) {
      IDS_HDT_CONSOLE_PSP_TRACE ("Error detected in the APOB DATA\n");
      return EFI_UNSUPPORTED;
    }
    ApobHeaderPtr = (APOB_BASE_HEADER *) (UINTN) ApobInfoPtr->ApobAddr;
    IDS_HDT_CONSOLE_PSP_TRACE ("ApobInfoPtr %x Supported %x ApobAddr %x ApobSize %x\n", ApobInfoPtr, ApobInfoPtr->Supported, ApobInfoPtr->ApobAddr, ApobInfoPtr->ApobSize);
  }


  IDS_HDT_CONSOLE_PSP_TRACE ("AmdPspGetApobEntry %x %x\n", GroupID, DataTypeID);
  IDS_HDT_CONSOLE_PSP_TRACE ("APOB Addr %x\n", ApobHeaderPtr);

  if (ApobHeaderPtr->Version >= 5) {
    ApobEntryBin = (UINT8 *) ApobHeaderPtr;
    ApobEntryBin += ApobHeaderPtr->OffsetOfFirstEntry;
  } else {
    IDS_HDT_CONSOLE_PSP_TRACE ("APOB version is not supported\n");
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }
  ApobEntry = (APOB_TYPE_HEADER *) ApobEntryBin;
  _NumofEntry = 0;

  while (ApobEntryBin  < ((UINT8 *) ApobHeaderPtr + ApobHeaderPtr->Size)) {
    //IDS_HDT_CONSOLE_PSP_TRACE ("ApobEntry @0x%x GroupID 0x%x TypeId 0x%x\n", ApobEntry, ApobEntry->GroupID, ApobEntry->DataTypeID);
    if ((ApobEntry->GroupID == GroupID) &&
        (ApobEntry->DataTypeID == DataTypeID)) {
      //Found a matched entry
      _NumofEntry++;
      *ApobEntries = ApobEntry;
      ApobEntries++;
      IDS_HDT_CONSOLE_PSP_TRACE ("Type found @0x%x\n", ApobEntry);
    }
    ApobEntryBin += (ApobEntry->TypeSize);
    ApobEntry = (APOB_TYPE_HEADER *) ApobEntryBin;
  }

  *NumofEntry = _NumofEntry;
  IDS_HDT_CONSOLE_PSP_TRACE ("Total  %d entries found\n", _NumofEntry);

  if (_NumofEntry == 0) {
    IDS_HDT_CONSOLE_PSP_TRACE ("ApobEntry NOT found\n", _NumofEntry);
    return EFI_NOT_FOUND;
  }

  return EFI_SUCCESS;
}


/**
 *  Return Entry instance as specified GroupId, DataTypeId, InstanceId
 *
 *  @param[in] GroupID GroupId of Apob entry
 *  @param[in] DataTypeID DataTypeID of Apob entry
 *  @param[out] InstanceID InstanceID of Apob entry
 *  @param[in] ReadFromSpiCopy TRUE force read from SPI copy
 *  @param[out] ApobEntry Point to the arrary which used to hold the ApobEntries
 *              ApobEntries arrary need be allocated outside of the routine
 *
 *  @retval       EFI_SUCCESS       Function succeed
 *  @retval       NON-ZERO          Error occurs
*/
EFI_STATUS
AmdPspGetApobEntryInstance (
  IN       UINT32  GroupID,
  IN       UINT32  DataTypeID,
  IN       UINT32  InstanceID,
  IN       BOOLEAN  ReadFromSpiCopy,
  OUT      APOB_TYPE_HEADER **ApobEntry
  )
{
  UINT32 i;
  UINT32 NumofInstance;
  APOB_TYPE_HEADER *_ApobEntries[APOB_ENTRY_INSTANCE_MAX];
  UINT32 _NumofEntry;
  APOB_TYPE_HEADER *_ApobEntry;

  *ApobEntry = NULL;
  _ApobEntry = NULL;
  IDS_HDT_CONSOLE_PSP_TRACE ("AmdPspGetApobEntryInstance %x %x %x\n", GroupID, DataTypeID, InstanceID);

  _NumofEntry = 0;
  AmdPspGetApobEntry (GroupID, DataTypeID, ReadFromSpiCopy, &_NumofEntry, &_ApobEntries[0]);
  if (_NumofEntry == 0) {
    IDS_HDT_CONSOLE_PSP_TRACE ("No entry found\n");
    return EFI_NOT_FOUND;
  }
  //Scan the Arrary to get the specific instance
  NumofInstance = 0;
  for (i = 0; i < _NumofEntry; i++) {
    if (_ApobEntries[i]->InstanceID == InstanceID) {
      NumofInstance++;
      _ApobEntry = _ApobEntries[i];
    }
  }
  //Instance ID can't be duplicated
  ASSERT (NumofInstance <= 1);

  if (NumofInstance == 0) {
    return EFI_NOT_FOUND;
  } else if (NumofInstance == 1) {
    IDS_HDT_CONSOLE_PSP_TRACE ("Instance found @0x%x\n", _ApobEntry);
    *ApobEntry = _ApobEntry;
    return EFI_SUCCESS;
  } else {
    return EFI_UNSUPPORTED;
  }
}

/**
 *  Get APOB address, and save to the HOB
 *
 *
 *  @retval EFI_SUCCESS       The APOB save to HOB successfully
 *
 **/
EFI_STATUS
EFIAPI
AmdPspApobLibConstructor (
  VOID
  )
{
  APOB_BASE_HEADER *ApobHeaderPtr;
  EFI_STATUS Status;
  VOID *GuidDataPtr;
  TYPE_ATTRIB       TypeAttrib;
  UINT64            EntryAddress;
  UINT32            EntrySize;
  UINT64            EntryDest;
  APOBLIB_INFO *ApobInfoPtr;
  APOBLIB_INFO ApobInfo;

  IDS_HDT_CONSOLE_PSP_TRACE ("AmdPspApobLibConstructor\n");

  //Exit if BR program
  if (SocFamilyIdentificationCheck (F15_BR_RAW_ID)) {
    return EFI_SUCCESS;
  }

  if (AmdPspGetApobInfo (&ApobInfoPtr) != EFI_SUCCESS) {
    //APOB Info data haven't been initialized
    IDS_HDT_CONSOLE_PSP_TRACE ("Init APOB HOB Info struct\n");
    //Check the existence of APOB entry in BIOS DIR, if not exit
    if (BIOSEntryInfo (BIOS_APOB_INFO, INSTANCE_IGNORED, &TypeAttrib, &EntryAddress, &EntrySize, &EntryDest) == FALSE) {
      IDS_HDT_CONSOLE_PSP_TRACE ("APOB Entry not found\n");
      return EFI_SUCCESS;
    }

    ApobHeaderPtr = (APOB_BASE_HEADER *) (UINTN) EntryDest;
    IDS_HDT_CONSOLE_PSP_TRACE ("APOB Addr %x\n", ApobHeaderPtr);
    //Signature verification failed
    if (ApobHeaderPtr->Signature != APOB_SIGNATURE) {
      IDS_HDT_CONSOLE_PSP_TRACE ("APOB SIG Check fail, APOB is not supported\n");
      return EFI_SUCCESS;
    }

    // Check APOB Size
    ASSERT (ApobHeaderPtr->Size != 0);
    ASSERT (ApobHeaderPtr->Size != 0xFFFFFFFFul);
    if ((ApobHeaderPtr->Size == 0) ||
        (ApobHeaderPtr->Size == 0xFFFFFFFFul)) {
      IDS_HDT_CONSOLE_PSP_TRACE ("APOB Size Check fail\n");
      return EFI_SUCCESS;
    }
    ApobInfo.Supported = TRUE;
    ApobInfo.ApobAddr = EntryDest;
    ApobInfo.ApobSize = ApobHeaderPtr->Size;

    //Publish the Info data to the HOB
    GuidDataPtr = BuildGuidDataHob (&gAmdPspApobHobGuid, (VOID *) &ApobInfo, EFI_PAGES_TO_SIZE (EFI_SIZE_TO_PAGES (sizeof (APOBLIB_INFO))));
    Status = ((GuidDataPtr == NULL) ? EFI_BAD_BUFFER_SIZE : EFI_SUCCESS);
    if (EFI_ERROR (Status)) {
      IDS_HDT_CONSOLE_PSP_TRACE ("APOB HOB Build fail\n");
    }
    IDS_HDT_CONSOLE_PSP_TRACE ("APOB HOB Build Success\n");
    //Reseve APOB region through Memory allocation HOB
    BuildMemoryAllocationHob (EntryDest, EFI_PAGES_TO_SIZE (EFI_SIZE_TO_PAGES (ApobHeaderPtr->Size)), EfiACPIMemoryNVS);
  }
  return EFI_SUCCESS;
}

