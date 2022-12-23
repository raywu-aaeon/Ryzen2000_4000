/* $NoKeywords:$ */
/**
 * @file
 *
 * AmdMemDmiConstruct.c
 *
 * Memory DMI table support.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Main)
 * @e \$Revision: 329870 $ @e \$Date: 2015-10-29 13:13:29 +0800 (Thu, 29 Oct 2015) $
 *
 **/
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
  *
 */

/*
 *----------------------------------------------------------------------------
 *                                MODULES USED
 *
 *----------------------------------------------------------------------------
 */

#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "Library/AmdHeapLib.h"
#include "mm.h"
#include "mn.h"
#include "mu.h"
#include "Library/AmdMemDmiConstructLib.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_FEATDMICONSTRUCTLIB_MEMDMICONSTRUCTLIB_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                           TYPEDEFS AND STRUCTURES
 *
 *----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
VOID
STATIC
IntToString (
  IN OUT   CHAR8 *String,
  IN       UINT8 *Integer,
  IN       UINT8 SizeInByte
);

/* -----------------------------------------------------------------------------*/
/**
 *  GetDmiInfoMain
 *
 *  Description:
 *     This is the common routine for getting Dmi type4 and type7 CPU related information.
 *
 *  Parameters:
 *    @param[in]        *StdHeader
 *    @param[in, out]  **DmiTable
 *
 *    @retval         AGESA_STATUS
 *
 */
AGESA_STATUS
MemConstructDmiInfo (
  IN       AMD_CONFIG_PARAMS     *StdHeader,
  IN OUT   DMI_INFO              **DmiTable
  )
{
  UINT8                         Socket;
  UINT8                         Channel;
  UINT8                         Dimm;
  UINT16                        DimmIndex;
  UINT8                         MaxPhysicalDimms;
  UINT8                         MaxLogicalDimms;
  UINT32                        EccCapable;
  UINT32                        MaxCapacity;
  UINT64                        Value64;
  UINT8                         TypeDetail;
  UINT32                       *TotalMemSizePtr;
  AGESA_STATUS                  Status;
  UINT8                        *MemInfo;
  DMI_T17_MEMORY_TYPE          *DmiType17MemTypePtr;
  DMI_T17_MEMORY_TYPE           MemType;
  MEM_DMI_PHYSICAL_DIMM_INFO   *DmiPhysicalDimmInfoTable;
  MEM_DMI_LOGICAL_DIMM_INFO    *DmiLogicalDimmInfoTable;
  DMI_INFO                     *DmiBufferPtr;
  ALLOCATE_HEAP_PARAMS          AllocateHeapParams;
  LOCATE_HEAP_PTR               LocateHeapParams;
  UINT8                         NumActiveDimms;

  MemInfo = NULL;
  DmiBufferPtr = *DmiTable;

  if (DmiBufferPtr == NULL) {
    //
    // Allocate a buffer by heap function
    //
    AllocateHeapParams.BufferHandle = AMD_DMI_INFO_BUFFER_HANDLE;
    AllocateHeapParams.RequestedBufferSize = sizeof (DMI_INFO);
    AllocateHeapParams.Persist = HEAP_SYSTEM_MEM;

    if (HeapAllocateBuffer (&AllocateHeapParams, StdHeader) != AGESA_SUCCESS) {
      return AGESA_ERROR;
    }

    DmiBufferPtr = (DMI_INFO *) AllocateHeapParams.BufferPtr;
    *DmiTable = DmiBufferPtr;
  }

  IDS_HDT_CONSOLE (MEM_FLOW, "  DMI is enabled\n");

  // Fill with 0x00
  LibAmdMemFill (DmiBufferPtr, 0x00, sizeof (DMI_INFO), StdHeader);

  //------------------------------
  // T Y P E 16 17 19 20
  //------------------------------

  LocateHeapParams.BufferHandle = AMD_DMI_MEM_DEV_INFO_HANDLE;
  Status = HeapLocateBuffer (&LocateHeapParams, StdHeader);
  if (Status != AGESA_SUCCESS) {
    return Status;
  } else {
    MemInfo = (UINT8 *) (LocateHeapParams.BufferPtr);
    // Max number of physical DIMMs
    MaxPhysicalDimms = *MemInfo;
    MemInfo ++;
    // Type Detail;
    TypeDetail = *MemInfo;
    MemInfo ++;
    // Pointer to total memory size
    TotalMemSizePtr = (UINT32 *) MemInfo;
    MemInfo += sizeof (UINT32);
    // ECC Type
    EccCapable = *((UINT32 *) MemInfo);
    MemInfo += sizeof (UINT32);
    // Memory Type
    DmiType17MemTypePtr = (DMI_T17_MEMORY_TYPE *) MemInfo;
    MemType = *DmiType17MemTypePtr;
    DmiType17MemTypePtr ++;
    MemInfo = (UINT8 *) DmiType17MemTypePtr;
    // Pointer to DMI info of Physical DIMMs
    DmiPhysicalDimmInfoTable = (MEM_DMI_PHYSICAL_DIMM_INFO *) MemInfo;
    // TYPE 16
    DmiBufferPtr->T16.Location = 0x03;
    DmiBufferPtr->T16.Use = 0x03;

    // TYPE 16 ECC Type
    if (EccCapable != 0) {
      DmiBufferPtr->T16.MemoryErrorCorrection = Dmi16MultiBitEcc;
    } else {
      DmiBufferPtr->T16.MemoryErrorCorrection = Dmi16NoneErrCorrection;
    }

    MaxCapacity = *TotalMemSizePtr;

    DmiBufferPtr->T16.NumberOfMemoryDevices = (UINT16) MaxPhysicalDimms;

    NumActiveDimms = 0;
    // TYPE 17 entries are organized by physical DIMMs
    for (DimmIndex = 0; DimmIndex < MaxPhysicalDimms; DimmIndex ++, DmiPhysicalDimmInfoTable ++) {
      Socket = DmiPhysicalDimmInfoTable->Socket;
      Channel = DmiPhysicalDimmInfoTable->Channel;
      Dimm = DmiPhysicalDimmInfoTable->Dimm;

      DmiBufferPtr->T17[Socket][Channel][Dimm].Handle = DmiPhysicalDimmInfoTable->Handle;
      DmiBufferPtr->T17[Socket][Channel][Dimm].TotalWidth = DmiPhysicalDimmInfoTable->TotalWidth;
      DmiBufferPtr->T17[Socket][Channel][Dimm].DataWidth = DmiPhysicalDimmInfoTable->DataWidth;
      DmiBufferPtr->T17[Socket][Channel][Dimm].MemorySize = DmiPhysicalDimmInfoTable->MemorySize;
      DmiBufferPtr->T17[Socket][Channel][Dimm].FormFactor = DmiPhysicalDimmInfoTable->FormFactor;
      DmiBufferPtr->T17[Socket][Channel][Dimm].DeviceSet = 0;

      DmiBufferPtr->T17[Socket][Channel][Dimm].DeviceLocator[0] = 'D';
      DmiBufferPtr->T17[Socket][Channel][Dimm].DeviceLocator[1] = 'I';
      DmiBufferPtr->T17[Socket][Channel][Dimm].DeviceLocator[2] = 'M';
      DmiBufferPtr->T17[Socket][Channel][Dimm].DeviceLocator[3] = 'M';
      DmiBufferPtr->T17[Socket][Channel][Dimm].DeviceLocator[4] = ' ';
      DmiBufferPtr->T17[Socket][Channel][Dimm].DeviceLocator[5] = Dimm + 0x30;
      DmiBufferPtr->T17[Socket][Channel][Dimm].DeviceLocator[6] = '\0';
      DmiBufferPtr->T17[Socket][Channel][Dimm].DeviceLocator[7] = '\0';

      DmiBufferPtr->T17[Socket][Channel][Dimm].BankLocator[0] = 'C';
      DmiBufferPtr->T17[Socket][Channel][Dimm].BankLocator[1] = 'H';
      DmiBufferPtr->T17[Socket][Channel][Dimm].BankLocator[2] = 'A';
      DmiBufferPtr->T17[Socket][Channel][Dimm].BankLocator[3] = 'N';
      DmiBufferPtr->T17[Socket][Channel][Dimm].BankLocator[4] = 'N';
      DmiBufferPtr->T17[Socket][Channel][Dimm].BankLocator[5] = 'E';
      DmiBufferPtr->T17[Socket][Channel][Dimm].BankLocator[6] = 'L';
      DmiBufferPtr->T17[Socket][Channel][Dimm].BankLocator[7] = ' ';
      DmiBufferPtr->T17[Socket][Channel][Dimm].BankLocator[8] = Channel + 0x41;
      DmiBufferPtr->T17[Socket][Channel][Dimm].BankLocator[9] = '\0';

      DmiBufferPtr->T17[Socket][Channel][Dimm].MemoryType = UnknownMemType;
      if (DmiPhysicalDimmInfoTable->MemorySize != 0) {
        DmiBufferPtr->T17[Socket][Channel][Dimm].MemoryType = MemType;
        NumActiveDimms ++;
        DmiBufferPtr->T17[Socket][Channel][Dimm].TypeDetail.Synchronous = 1;
        if (TypeDetail == 1) {
          DmiBufferPtr->T17[Socket][Channel][Dimm].TypeDetail.Registered = 1;
        } else if  (TypeDetail == 2) {
          DmiBufferPtr->T17[Socket][Channel][Dimm].TypeDetail.Unbuffered = 1;
        } else {
          DmiBufferPtr->T17[Socket][Channel][Dimm].TypeDetail.Unknown = 1;
        }
      }
      DmiBufferPtr->T17[Socket][Channel][Dimm].Speed = DmiPhysicalDimmInfoTable->Speed;

      DmiBufferPtr->T17[Socket][Channel][Dimm].ManufacturerIdCode = DmiPhysicalDimmInfoTable->ManufacturerIdCode;

      IntToString (DmiBufferPtr->T17[Socket][Channel][Dimm].SerialNumber, DmiPhysicalDimmInfoTable->SerialNumber, (sizeof DmiBufferPtr->T17[Socket][Channel][Dimm].SerialNumber - 1) / 2);

      LibAmdMemCopy (&DmiBufferPtr->T17[Socket][Channel][Dimm].PartNumber, &DmiPhysicalDimmInfoTable->PartNumber, sizeof (DmiBufferPtr->T17[Socket][Channel][Dimm].PartNumber), StdHeader);

      DmiBufferPtr->T17[Socket][Channel][Dimm].Attributes = DmiPhysicalDimmInfoTable->Attributes;
      DmiBufferPtr->T17[Socket][Channel][Dimm].ExtSize = DmiPhysicalDimmInfoTable->ExtSize;
      DmiBufferPtr->T17[Socket][Channel][Dimm].ConfigSpeed = DmiPhysicalDimmInfoTable->ConfigSpeed;
      DmiBufferPtr->T17[Socket][Channel][Dimm].MinimumVoltage = DmiPhysicalDimmInfoTable->MinimumVoltage;
      DmiBufferPtr->T17[Socket][Channel][Dimm].MaximumVoltage = DmiPhysicalDimmInfoTable->MaximumVoltage;
      DmiBufferPtr->T17[Socket][Channel][Dimm].ConfiguredVoltage = DmiPhysicalDimmInfoTable->ConfiguredVoltage;
    }

    // Max number of logical DIMMs
    MemInfo = (UINT8 *) DmiPhysicalDimmInfoTable;
    MaxLogicalDimms = *MemInfo;
    MemInfo ++;

    // Pointer to DMI info of Logical DIMMs
    DmiLogicalDimmInfoTable = (MEM_DMI_LOGICAL_DIMM_INFO *) MemInfo;

    // TYPE 20 entries are organized by logical DIMMs
    for (DimmIndex = 0; DimmIndex < MaxLogicalDimms; DimmIndex ++, DmiLogicalDimmInfoTable ++) {
      Socket = DmiLogicalDimmInfoTable->Socket;
      Channel = DmiLogicalDimmInfoTable->Channel;
      Dimm = DmiLogicalDimmInfoTable->Dimm;
      DmiBufferPtr->T20[Socket][Channel][Dimm].PartitionRowPosition = 0xFF;
      if (DmiLogicalDimmInfoTable->Interleaved) {
        DmiBufferPtr->T20[Socket][Channel][Dimm].InterleavePosition = 0xFF;
        DmiBufferPtr->T20[Socket][Channel][Dimm].InterleavedDataDepth = 0xFF;
      }

      if (DmiLogicalDimmInfoTable->DimmPresent) {
        DmiBufferPtr->T20[Socket][Channel][Dimm].MemoryDeviceHandle = DmiLogicalDimmInfoTable->MemoryDeviceHandle;
        DmiBufferPtr->T20[Socket][Channel][Dimm].StartingAddr = DmiLogicalDimmInfoTable->StartingAddr;
        DmiBufferPtr->T20[Socket][Channel][Dimm].EndingAddr = DmiLogicalDimmInfoTable->EndingAddr;
        DmiBufferPtr->T20[Socket][Channel][Dimm].ExtStartingAddr = DmiLogicalDimmInfoTable->ExtStartingAddr;
        DmiBufferPtr->T20[Socket][Channel][Dimm].ExtEndingAddr = DmiLogicalDimmInfoTable->ExtEndingAddr;
      }
    }

    // TYPE 19
    DmiBufferPtr->T19[0].StartingAddr = 0;
    DmiBufferPtr->T19[0].ExtStartingAddr = 0;
    DmiBufferPtr->T19[0].ExtEndingAddr = 0;

    // If Ending Address >= 0xFFFFFFFF, update Starting Address (offset 04h) & Ending Address (offset 08h) to 0xFFFFFFFF,
    // and use the Extended Starting Address (offset 0Fh) & Extended Ending Address (offset 17h) instead.
    Value64 = (UINT64) ((MaxCapacity << 10) - 1);
    // Value64 = EndingAddr = MaxCapacity in KByte - 1
    if (Value64 >= ((UINT64) 0xFFFFFFFF)) {
      DmiBufferPtr->T19[0].StartingAddr = 0xFFFFFFFFUL;
      DmiBufferPtr->T19[0].EndingAddr = 0xFFFFFFFFUL;
      // In Byte
      DmiBufferPtr->T19[0].ExtEndingAddr = Value64 << 10;
    } else {
      // In KByte
      DmiBufferPtr->T19[0].EndingAddr = (UINT32) Value64;
    }

    DmiBufferPtr->T19[0].PartitionWidth = NumActiveDimms;
  }
  return AGESA_SUCCESS;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  IntToString
 *
 *  Description:
 *    Translate UINT array to CHAR array.
 *
 *  Parameters:
 *    @param[in, out]    *String       Pointer to CHAR array
 *    @param[in]         *Integer      Pointer to UINT array
 *    @param[in]         SizeInByte    The size of UINT array
 *
 *  Processing:
 *
 */
VOID
STATIC
IntToString (
  IN OUT   CHAR8 *String,
  IN       UINT8 *Integer,
  IN       UINT8 SizeInByte
  )
{
  UINT8 Index;

  for (Index = 0; Index < SizeInByte; Index++) {
    *(String + Index * 2) = (*(Integer + Index) >> 4) & 0x0F;
    *(String + Index * 2 + 1) = *(Integer + Index) & 0x0F;
  }
  for (Index = 0; Index < (SizeInByte * 2); Index++) {
    if (*(String + Index) >= 0x0A) {
      *(String + Index) += 0x37;
    } else {
      *(String + Index) += 0x30;
    }
  }
  *(String + SizeInByte * 2) = 0x0;
}
