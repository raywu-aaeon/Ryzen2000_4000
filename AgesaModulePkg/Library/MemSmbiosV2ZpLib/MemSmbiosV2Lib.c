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

#include <Library/BaseLib.h>
#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "Library/AmdHeapLib.h"
#include "mm.h"
#include "mn.h"
#include "mu.h"
#include "mtspd4.h"
#include "MemDmi.h"
#include <Addendum/Apcb/Inc/ZP/APOB.h>
#include <Library/AmdPspApobLib.h>
#include "Library/AmdCalloutLib.h"
#include "Library/MemChanXLat.h"
#include <Guid/AmdMemoryInfoHob.h>
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEMSMBIOSV2LIB_MEMSMBIOSV2LIB_FILECODE
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
 *  TranslateChannelInfo
 *
 *  Description:
 *     Translate the channel Id depending upon the channel translation table.
 *
 *  Parameters:
 *    @param[in]        RequestedChannelId - The requested channel Id
 *    @param[out]       *TranslatedChannelId - Pointer to the translated Id
 *    @param[in]        *XlatTable - Pointer to the memory channel translation table
 *
 */
VOID
STATIC
TranslateChannelInfo (
  IN       UINT8 RequestedChannelId,
  OUT      UINT8 *TranslatedChannelId,
  IN       HOST_TO_APCB_CHANNEL_XLAT *XlatTable
  )
{
  UINT8 Index;

  *TranslatedChannelId = RequestedChannelId;

  if (XlatTable != NULL) {
    Index = 0;
    while (XlatTable->RequestedChannelId != 0xFF) {
      if (RequestedChannelId == XlatTable->RequestedChannelId) {
        *TranslatedChannelId = XlatTable->TranslatedChannelId;
        return;
      }
      XlatTable++;
    }
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *  GetPhysicalDimmInfoD4
 *
 *  Description:
 *     Obtain the physical DIMM information from SPD data.
 *
 *  Parameters:
 *    @param[in, out]  T17           - Pointer to TYPE17_DMI_INFO
 *    @param[in]       *PhysicalDimm - Pointer to the physical DIMM info
 *    @param[in]       *StdHeader   - Pointer to AMD_CONFIG_PARAMS
 *
 *    @retval          BOOLEAN
 *
 */
BOOLEAN
STATIC
GetPhysicalDimmInfoD4 (
  IN OUT   TYPE17_DMI_INFO *T17,
  IN       APOB_MEM_DMI_PHYSICAL_DIMM  *PhysicalDimm,
  IN       AMD_CONFIG_PARAMS *StdHeader,
  IN       UINT8 TranslatedChannel
  )
{
  UINT16                i;
  UINT8                 Socket;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT8                 DimmSpd[512];
  AGESA_READ_SPD_PARAMS ReadSpd;
  AGESA_STATUS          AgesaStatus;
  UINT8                 DataWidth;
  UINT16                Capacity;
  UINT16                BusWidth;
  UINT16                Width;
  UINT8                 Rank;
  UINT32                MemorySize;
  INT32                 MTB_ps;
  INT32                 FTB_ps;
  INT32                 Value32;
  UINT8                 VoltageMap;
  APOB_TYPE_HEADER      *ApobEntry;
  EFI_STATUS            ApobStatus;
  APOB_MEM_DIMM_SPD_DATA_STRUCT ApobSpdHeader;
  UINT8                 Chan;
  UINT8                 j;
  UINT16                Instance;
  UINT16                DieLoop;
  UINT8                 DimmIndex;

//  UINT32 ManufacturerIdCode;

  Socket  = PhysicalDimm->Socket;
  Channel = PhysicalDimm->Channel;
  Dimm    = PhysicalDimm->Dimm;
  T17->Handle = PhysicalDimm->Handle;
  T17->DeviceSet = 0;

  T17->DeviceLocator[0] = 'D';
  T17->DeviceLocator[1] = 'I';
  T17->DeviceLocator[2] = 'M';
  T17->DeviceLocator[3] = 'M';
  T17->DeviceLocator[4] = ' ';
  T17->DeviceLocator[5] = Dimm + 0x30;
  T17->DeviceLocator[6] = '\0';
  T17->DeviceLocator[7] = '\0';

  T17->BankLocator[0] = 'P';
  T17->BankLocator[1] = Socket + 0x30;
  T17->BankLocator[2] = ' ';
  T17->BankLocator[3] = 'C';
  T17->BankLocator[4] = 'H';
  T17->BankLocator[5] = 'A';
  T17->BankLocator[6] = 'N';
  T17->BankLocator[7] = 'N';
  T17->BankLocator[8] = 'E';
  T17->BankLocator[9] = 'L';
  T17->BankLocator[10] = ' ';
  T17->BankLocator[11] = TranslatedChannel + 0x41;
  T17->BankLocator[12] = '\0';

  if (PhysicalDimm->DimmPresent) {
    ReadSpd.SocketId = Socket;
    ReadSpd.MemChannelId = TranslatedChannel;
    ReadSpd.DimmId = Dimm;

    ReadSpd.Buffer = &DimmSpd[0];
    LibAmdMemCopy (&ReadSpd.StdHeader, StdHeader, sizeof (AMD_CONFIG_PARAMS), StdHeader);

    IDS_HDT_CONSOLE (MAIN_FLOW, "SPD Socket %d Channel %d Dimm %d: %08x\n", Socket, Channel, Dimm, DimmSpd);
    AGESA_TESTPOINT (TpProcMemBeforeAgesaReadSpd, StdHeader);
    // Get SPD Data from APOB
    ApobEntry = NULL;
    DieLoop = 0;
    AgesaStatus = AGESA_UNSUPPORTED;
    for (DieLoop = 0; DieLoop < ABL_APOB_MAX_DIES_PER_SOCKET; DieLoop++) {
    //Instance = (TranslatedChannel >> 1);
      Instance = DieLoop;
      Instance |= ((Socket & 0x000000FF) << 8);
      IDS_HDT_CONSOLE (MAIN_FLOW, "Get Spd Data from APOB for Socket %d, Die %d , Channel %d Instance %d\n", Socket, DieLoop, TranslatedChannel, Instance);
    ApobStatus = AmdPspGetApobEntryInstance (APOB_MEM, APOB_MEM_DIMM_SPD_DATA_TYPE, Instance, FALSE, &ApobEntry);
      if (ApobStatus == EFI_SUCCESS) {
        LibAmdMemCopy (&ApobSpdHeader, ApobEntry, sizeof (APOB_MEM_DIMM_SPD_DATA_STRUCT), StdHeader);
        for (Chan = 0; Chan < ApobSpdHeader.MaxChannelsPerSocket; Chan++) {
          for (j = 0; j < ApobSpdHeader.MaxDimmsPerChannel; j++) {
            DimmIndex = j + Chan * ApobSpdHeader.MaxDimmsPerChannel;
            if (ApobSpdHeader.DimmSmbusInfo[DimmIndex].DimmPresent == TRUE) {
              if (ApobSpdHeader.DimmSmbusInfo[DimmIndex].SocketNumber == Socket) {
                if (ApobSpdHeader.DimmSmbusInfo[DimmIndex].ChannelNumber == Channel) {
                  if (ApobSpdHeader.DimmSmbusInfo[DimmIndex].DimmNumber == Dimm) {
                    LibAmdMemCopy (DimmSpd, ApobSpdHeader.DimmSmbusInfo[DimmIndex].Data, 512, StdHeader);
                    AgesaStatus = AGESA_SUCCESS;
                    break;
                  }
                }
              }
            }
          }
          if (AgesaStatus == AGESA_SUCCESS){
            break;
          }
        }
      }
      if (AgesaStatus == AGESA_SUCCESS){
        break;
      }
    }
    if (AgesaStatus != AGESA_SUCCESS) {
      IDS_HDT_CONSOLE (MAIN_FLOW, "Get Spd Data from SMBUS\n");
      AgesaStatus = AgesaReadSpd (0, &ReadSpd);
    }
    AGESA_TESTPOINT (TpProcMemAfterAgesaReadSpd, StdHeader);

    ASSERT (AGESA_SUCCESS == AgesaStatus);

    for (i = 0; i < 512; i ++) {
      if (0 == i % 16) {
        IDS_HDT_CONSOLE (MAIN_FLOW, "\n\t");
      }
      IDS_HDT_CONSOLE (MAIN_FLOW, "%02x ", DimmSpd[i]);
    }
    IDS_HDT_CONSOLE (MAIN_FLOW, "\n");

    DataWidth = 1 << ((DimmSpd[SPD_BUS_WIDTH] & BUSWIDTH_MASK) + 3);
    T17->DataWidth = DataWidth;
    T17->TotalWidth = T17->DataWidth + 8 * (DimmSpd[SPD_BUSWIDTH_EXT] & BUSWIDTH_EXT_ECC);

    Capacity = 0x100 << (DimmSpd[SPD_CAPACITY] & CAPACITY_MASK);
    ASSERT (Capacity <= 0x8000);
    BusWidth = 8 << (DimmSpd[SPD_BUS_WIDTH] & BUSWIDTH_MASK);
    ASSERT (BusWidth <= 64);
    Width = 4 << (DimmSpd[SPD_DEVICE_WIDTH] & DEVICE_WIDTH_MASK);
    ASSERT (Width <= 32);
    Rank = 1 + (DimmSpd[SPD_RANKS] >> RANKS_SHIFT) & RANKS_MASK;
    ASSERT (Rank <= 4);
    MemorySize = Capacity / 8 * BusWidth / Width * Rank;
    if (MemorySize < 0x7FFF) {
      T17->MemorySize = (UINT16)MemorySize;
      T17->ExtSize = 0;
    } else {
      T17->MemorySize = 0x7FFF;
      T17->ExtSize = MemorySize;
    }

    T17->TypeDetail.Synchronous = 1;

    switch (DimmSpd[SPD_BASE_MODULE_TYPE] & MODULE_TYPE_MASK) {
    case 0x01:    // RDIMM
      T17->TypeDetail.Registered = 1;
      T17->FormFactor = DimmFormFactorFormFactor;
      break;
    case 0x02:    // UDIMM
      T17->TypeDetail.Unbuffered = 1;
      T17->FormFactor = DimmFormFactorFormFactor;
      break;
    case 0x04:    // LRDIMM
      T17->TypeDetail.Registered = 1;
      T17->FormFactor = DimmFormFactorFormFactor;
      break;
    case 0x03:    // SO-DIMM
    case 0x08:    // 72b-SO-RDIMM
    case 0x09:    // 72b-SO-UDIMM
    case 0x0A:    // 16b-SO-DIMM
    case 0x0B:    // 32b-SO-DIMM
      T17->TypeDetail.Unbuffered = 1;
      T17->FormFactor = SodimmFormFactor;
      break;
    default:
      T17->TypeDetail.Unknown = 1;
      T17->FormFactor = UnknowFormFactor;
    }

    T17->MemoryType = Ddr4MemType;

    MTB_ps = (((DimmSpd[SPD_MEDIUM_TIMEBASE] >> MTB_SHIFT) & MTB_MSK) == 0) ? 125 : 0;
    FTB_ps = ((DimmSpd[SPD_FINE_TIMEBASE] & FTB_MSK) == 0) ? 1 : 0;
    Value32 = (MTB_ps * DimmSpd[SPD_TCK]) + (FTB_ps * (INT8) DimmSpd[SPD_TCK_FTB]);

    if ((Value32 <= 625)) {
      T17->Speed = 1600;              // DDR4-3200
    } else if (Value32 <= 682) {
      T17->Speed = 1467;              // DDR4-2933
    } else if (Value32 <= 750) {
      T17->Speed = 1333;              // DDR4-2667
    } else if (Value32 <= 834) {
      T17->Speed = 1200;              // DDR4-2400
    } else if (Value32 <= 938) {
      T17->Speed = 1067;              // DDR4-2133
    } else if (Value32 <= 1071) {
      T17->Speed = 933;               // DDR4-1866
    } else if (Value32 <= 1250) {
      T17->Speed = 800;               // DDR4-1600
    } else {
      T17->Speed = 667;               // DDR4-1333
    }

    T17->ManufacturerIdCode = (DimmSpd[SPD_MANUFACTURER_ID_MSB] << 8) | DimmSpd[SPD_MANUFACTURER_ID_LSB];
    IntToString (T17->SerialNumber, &DimmSpd[SPD_SERIAL_NUMBER], (sizeof (T17->SerialNumber) - 1) / 2);
    for (i = 0; i < sizeof (T17->PartNumber) - 1; i ++) {
      T17->PartNumber[i] = DimmSpd[i + SPD_PART_NUMBER];
    }
    T17->PartNumber[i] = 0;

    T17->Attributes = Rank;

    VoltageMap = DimmSpd[SPD_DRAM_VDD];
    T17->MinimumVoltage = CONVERT_ENCODED_TO_VDDIO_MILLIVOLTS ((HighBitSet32 (VoltageMap) & 0xFE), DDR4_TECHNOLOGY);
    T17->MaximumVoltage = CONVERT_ENCODED_TO_VDDIO_MILLIVOLTS ((LowBitSet32 (VoltageMap) & 0xFE), DDR4_TECHNOLOGY);

    T17->ConfigSpeed = PhysicalDimm->ConfigSpeed;
    T17->ConfiguredVoltage = PhysicalDimm->ConfigVoltage;

    return TRUE;

  } else {
    IDS_HDT_CONSOLE (MAIN_FLOW, "Dummy Type 17 Created for Socket %d, Channel %d, Dimm %d\n", Socket, Channel, Dimm);
    T17->DataWidth = 0xFFFF;
    T17->TotalWidth = 0xFFFF;
    T17->MemorySize = 0;
    T17->ExtSize = 0;
    T17->TypeDetail.Unknown = 1;
    T17->FormFactor = UnknowFormFactor;
    T17->MemoryType = UnknownMemType;
    T17->Speed = 0;
    T17->ManufacturerIdCode = 0;

    for (i = 0; i < sizeof (T17->SerialNumber); i++) {
      T17->SerialNumber[i] = 0x0;
    }

    for (i = 0; i < sizeof (T17->PartNumber); i++) {
      T17->PartNumber[i] = 0x0;
    }

    T17->Attributes = 0;
    T17->MinimumVoltage = 0;
    T17->MaximumVoltage = 0;
    T17->ConfigSpeed = 0;
    T17->ConfiguredVoltage = 0;

    return FALSE;
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *  GetLogicalDimmInfo
 *
 *  Description:
 *     Obtain the logical DIMM information for Type 20.
 *
 *  Parameters:
 *    @param[in]        T20 - Pointer to TYPE20_DMI_INFO
 *    @param[out]       *LogicalDimm - Pointer to the logical DIMM info
 *
 *    @retval         BOOLEAN
 *
 */
BOOLEAN
GetLogicalDimmInfo (
  IN OUT   TYPE20_DMI_INFO *T20,
  IN       APOB_MEM_DMI_LOGICAL_DIMM *LogicalDimm
  )
{
  if (1 == LogicalDimm->DimmPresent) {
    T20->MemoryDeviceHandle = LogicalDimm->MemoryDeviceHandle;
    T20->PartitionRowPosition = 0xFF;
    T20->InterleavePosition   = 0;
    T20->InterleavedDataDepth = 0;
    if (1 == LogicalDimm->Interleaved) {
      T20->InterleavePosition = 0xFF;
      T20->InterleavedDataDepth = 0xFF;
    }
    T20->StartingAddr       = LogicalDimm->StartingAddr;
    T20->EndingAddr         = LogicalDimm->EndingAddr;
    T20->ExtStartingAddr    = LogicalDimm->UnifiedExtStartingAddr.ExtStartingAddr;
    T20->ExtEndingAddr      = LogicalDimm->UnifiedExtEndingAddr.ExtEndingAddr;
  }

  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *  GetMemSmbiosV2
 *
 *  Description:
 *     This is the common routine for getting DMI Type 16, Type 17, Type 19 and Type 20 related information.
 *
 *  Parameters:
 *    @param[in]        DramType - DRAM Type
 *    @param[in]        *ApobSmbiosInfo - Pointer to the APOB SMBIOS data block
 *    @param[in]        *MemChanXLatTab - Pointer to the memory channel translation table
 *    @param[in]        *StdHeader - Pointer to AMD_CONFIG_PARAMS
 *
 *    @retval         AGESA_STATUS
 *
 */
AGESA_STATUS
GetMemSmbiosV2 (
  IN       UINT8                       DramType,
  IN       UINT8                       NumSockets,
  IN       VOID                        *ApobSmbiosInfo,
  IN       HOST_TO_APCB_CHANNEL_XLAT   *MemChanXLatTab,
  IN       AMD_CONFIG_PARAMS           *StdHeader,
  IN       AMD_MEMORY_INFO_HOB         *AmdMemoryInfoHob
  )
{
  UINT8                         Socket;
  UINT8                         Channel;
  UINT8                         Dimm;
  UINT16                        DimmIndex;
  UINT8                         MaxPhysicalDimms;
  UINT8                         MaxLogicalDimms;
  UINT64                        Value64;
  DMI_INFO                      *DmiBuffer;
  ALLOCATE_HEAP_PARAMS          AllocateHeapParams;
  APOB_MEM_DMI_HEADER           *ApobMemDmiHeader;
  UINT32                        TotalMemSize;
  APOB_MEM_DMI_PHYSICAL_DIMM    *PhysicalDimm;
  APOB_MEM_DMI_LOGICAL_DIMM     *LogicalDimm;
  UINT8                         NumActiveDimms;
  UINT8                         TranslatedChannel;
  //
  // Allocate a buffer by heap function
  //
  AllocateHeapParams.BufferHandle = AMD_DMI_INFO_BUFFER_HANDLE;
  AllocateHeapParams.RequestedBufferSize = sizeof (DMI_INFO);
  AllocateHeapParams.Persist = HEAP_SYSTEM_MEM;

  if (HeapAllocateBuffer (&AllocateHeapParams, StdHeader) != AGESA_SUCCESS) {
    ASSERT (FALSE);
    return AGESA_ERROR;
  }

  DmiBuffer = (DMI_INFO *) AllocateHeapParams.BufferPtr;

  IDS_HDT_CONSOLE (MAIN_FLOW, "\tDMI enabled\n");
  // Fill with 0x00
  LibAmdMemFill (DmiBuffer, 0x00, sizeof (DMI_INFO), StdHeader);

  ASSERT (ApobSmbiosInfo != NULL);
  ApobMemDmiHeader = (APOB_MEM_DMI_HEADER *)ApobSmbiosInfo;
  MaxPhysicalDimms = ApobMemDmiHeader->MaxPhysicalDimms;
  MaxLogicalDimms = ApobMemDmiHeader->MaxLogicalDimms;
  TotalMemSize = 0;
  PhysicalDimm = (APOB_MEM_DMI_PHYSICAL_DIMM *)&ApobMemDmiHeader[1];

  // Type 16 construction
  DmiBuffer->T16.Location = 0x03;
  DmiBuffer->T16.Use = 0x03;
  DmiBuffer->T16.NumberOfMemoryDevices = MaxPhysicalDimms;
  DmiBuffer->T16.MemoryErrorCorrection = (ApobMemDmiHeader->EccCapable != 0) ? Dmi16MultiBitEcc : Dmi16NoneErrCorrection;

  NumActiveDimms = 0;
  // TYPE 17 entries are organized by physical DIMMs
  for (DimmIndex = 0; DimmIndex < MaxPhysicalDimms; DimmIndex ++, PhysicalDimm ++) {
    Socket  = PhysicalDimm->Socket;
    TranslatedChannel = PhysicalDimm->Channel;
    TranslateChannelInfo (PhysicalDimm->Channel, &TranslatedChannel, MemChanXLatTab);
    Dimm    = PhysicalDimm->Dimm;
    if (GetPhysicalDimmInfoD4 (&DmiBuffer->T17[Socket][TranslatedChannel][Dimm], PhysicalDimm, StdHeader, TranslatedChannel)) {
      NumActiveDimms ++;
    }
    TotalMemSize += (DmiBuffer->T17[Socket][TranslatedChannel][Dimm].MemorySize != 0x7FFF) ?
                      DmiBuffer->T17[Socket][TranslatedChannel][Dimm].MemorySize : DmiBuffer->T17[Socket][TranslatedChannel][Dimm].ExtSize;
  }

  // Pointer to DMI info of Logical DIMMs
  LogicalDimm = (APOB_MEM_DMI_LOGICAL_DIMM *) PhysicalDimm;

  // TYPE 20 entries are organized by logical DIMMs
  for (DimmIndex = 0; DimmIndex < MaxLogicalDimms; DimmIndex ++, LogicalDimm ++) {
    Socket  = LogicalDimm->Socket;
    TranslateChannelInfo (LogicalDimm->Channel, &Channel, MemChanXLatTab);
    if (Channel != 0xFF) {
      LogicalDimm->Channel = Channel;
      Dimm    = LogicalDimm->Dimm;
      GetLogicalDimmInfo (&DmiBuffer->T20[Socket][Channel][Dimm], LogicalDimm);   
    }
  }

  // TYPE 19
  DmiBuffer->T19[0].StartingAddr    = 0;
  DmiBuffer->T19[0].ExtStartingAddr = 0;
  DmiBuffer->T19[0].ExtEndingAddr   = 0;

  // If Ending Address >= 0xFFFFFFFF, update Starting Address (offset 04h) & Ending Address (offset 08h) to 0xFFFFFFFF,
  // and use the Extended Starting Address (offset 0Fh) & Extended Ending Address (offset 17h) instead.
  Value64 = (((UINT64) TotalMemSize << 10) - 1);
  if (Value64 >= ((UINT64) 0xFFFFFFFF)) {
    DmiBuffer->T19[0].StartingAddr = 0xFFFFFFFFUL;
    DmiBuffer->T19[0].EndingAddr = 0xFFFFFFFFUL;
    // In Byte
    DmiBuffer->T19[0].ExtEndingAddr = LShiftU64 (Value64, 10);
  } else {
    // In KByte
    DmiBuffer->T19[0].EndingAddr = (UINT32) Value64;
  }

  DmiBuffer->T19[0].PartitionWidth = NumActiveDimms;

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

