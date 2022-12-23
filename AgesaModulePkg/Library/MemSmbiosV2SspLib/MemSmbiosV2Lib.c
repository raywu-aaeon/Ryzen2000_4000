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
#include <Addendum/Apcb/Inc/Ssp/APOB.h>
#include <Library/AmdPspApobLib.h>
#include "Library/AmdCalloutLib.h"
#include "Library/MemChanXLat.h"
#include <Guid/AmdMemoryInfoHob.h>
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEMSMBIOSV2LIB_MEMSMBIOSV2LIB_FILECODE
extern EFI_GUID gAmdNvdimmSpdInfoHobGuid;

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
#pragma pack (1)
///< Buffer for each NVDIMM, keep SPD data for ACPI NFIT table
typedef struct {
  UINT16    DataValid;                ///< 0x55aa --> data valid in this entry
  UINT8     Socket;                   ///< Socket
  UINT8     Channel;                  ///< Channel
  UINT8     Dimm;                     ///< Dimm
  UINT16    NvdimmIndex;              ///< Dimm index
  UINT16    Handle;                   ///< TYPE17->Handle
  UINT16    Spd192;                   ///< 
  UINT16    Spd194;                   ///< 
  UINT16    Spd196;                   ///< 
  UINT16    Spd198;                   ///< High byte reserved, set to 0
  UINT16    Spd320;                   ///< 
  UINT16    Spd322;                   ///< High byte reserved, set to 0
  UINT16    Spd323;                   ///< 
  UINT8     SerialNumber[4];          ///< SPD 325 ~ 328
  UINT16    Spd349;                   ///< High byte reserved, set to 0
  UINT16    Reserved;                 ///< Reserved
} NVDIMM_SPD_INFO;
#pragma pack ()

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

VOID *
EFIAPI
BuildGuidDataHob (
  IN CONST EFI_GUID              *Guid,
  IN VOID                        *Data,
  IN UINTN                       DataLength
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
  IN OUT   NVDIMM_SPD_INFO    **nvdimmSpdInfo,
  IN       AMD_CONFIG_PARAMS  *StdHeader
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
  T17->BankLocator[11] = Channel + 0x41;
  T17->BankLocator[12] = '\0';

  IDS_HDT_CONSOLE (MAIN_FLOW, "T17 Handle = %x\n", T17->Handle);
  if (PhysicalDimm->DimmPresent) {
    ReadSpd.SocketId = Socket;
    ReadSpd.MemChannelId = Channel;
    ReadSpd.DimmId = Dimm;

    ReadSpd.Buffer = &DimmSpd[0];
    LibAmdMemCopy (&ReadSpd.StdHeader, StdHeader, sizeof (AMD_CONFIG_PARAMS), StdHeader);

    IDS_HDT_CONSOLE (MAIN_FLOW, "SPD Socket %d Channel %d Dimm %d: %08x\n", Socket, Channel, Dimm, DimmSpd);
    AGESA_TESTPOINT (TpProcMemBeforeAgesaReadSpd, StdHeader);
    AgesaStatus = AgesaReadSpd (0, &ReadSpd);
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

    // Save NVDIMM SPD data to nvdimmSpdInfo
    if ((HYBRID_TYPE == ((DimmSpd[SPD_HYBRID] >> HYBRID_SHIFT) & HYBRID_MASK)) &&
        (NVDIMM_HYBRID == ((DimmSpd[SPD_HYBRID_MEDIA] >> HYBRID_MEDIA_SHIFT) & HYBRID_MEDIA_MASK))) {
      (*nvdimmSpdInfo)->DataValid = 0x55aa;
      (*nvdimmSpdInfo)->Handle = T17->Handle;
      (*nvdimmSpdInfo)->Spd192 = ((UINT16) DimmSpd[193] << 8) | (UINT16) DimmSpd[192];
      (*nvdimmSpdInfo)->Spd194 = ((UINT16) DimmSpd[195] << 8) | (UINT16) DimmSpd[194];
      (*nvdimmSpdInfo)->Spd196 = ((UINT16) DimmSpd[197] << 8) | (UINT16) DimmSpd[196];
      (*nvdimmSpdInfo)->Spd198 = (UINT16) DimmSpd[198];
      (*nvdimmSpdInfo)->Spd320 = ((UINT16) DimmSpd[321] << 8) | (UINT16) DimmSpd[320];
      (*nvdimmSpdInfo)->Spd322 = (UINT16) DimmSpd[322];
      (*nvdimmSpdInfo)->Spd323 = ((UINT16) DimmSpd[324] << 8) | (UINT16) DimmSpd[323];
      (*nvdimmSpdInfo)->SerialNumber[0] = DimmSpd[325];
      (*nvdimmSpdInfo)->SerialNumber[1] = DimmSpd[326];
      (*nvdimmSpdInfo)->SerialNumber[2] = DimmSpd[327];
      (*nvdimmSpdInfo)->SerialNumber[3] = DimmSpd[328];
      (*nvdimmSpdInfo)->Spd349 = (UINT16) DimmSpd[349];
      //IDS_HDT_CONSOLE (MAIN_FLOW, "\tNvdimm Index=%x, Handle=%x, 192=%04x, 194=%04x, 196=%04x, 198=%04x, 320=%04x, 322=%04x, 323=%04x, serial=%02x%02x%02x%02x, 349=%04x\n",\
      //                 nvdimmSpdInfo->NvdimmIndex,nvdimmSpdInfo->Handle,nvdimmSpdInfo->Spd192,nvdimmSpdInfo->Spd194,nvdimmSpdInfo->Spd196,nvdimmSpdInfo->Spd198,\
      //                 nvdimmSpdInfo->Spd320,nvdimmSpdInfo->Spd322,nvdimmSpdInfo->Spd323,nvdimmSpdInfo->SerialNumber[3],nvdimmSpdInfo->SerialNumber[2],\
      //                 nvdimmSpdInfo->SerialNumber[1],nvdimmSpdInfo->SerialNumber[0],nvdimmSpdInfo->Spd349);
      (*nvdimmSpdInfo)++;    // Move pointer to next available location
    }
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
  }

  return TRUE;
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
  UINT8                         MaxChannel;
  UINT8                         MaxDimm;
  UINT16                        DimmIndex;
  UINT8                         MaxPhysicalDimms;
  UINT8                         MaxLogicalDimms;
  UINT16                        MaxHandle;
  DMI_INFO                      *DmiBuffer;
  ALLOCATE_HEAP_PARAMS          AllocateHeapParams;
  APOB_MEM_DMI_HEADER           *ApobMemDmiHeader;
  UINT32                        TotalMemSize;
  APOB_MEM_DMI_PHYSICAL_DIMM    *PhysicalDimm;
  APOB_MEM_DMI_LOGICAL_DIMM     *LogicalDimm;
  APOB_MEM_DMI_PHYSICAL_DIMM    DummyPhysicalDimm;
  UINT8                         NumActiveDimms;
  BOOLEAN                       SocketScanned[MAX_SOCKETS_SUPPORTED];
  NVDIMM_SPD_INFO               *nvdimmSpdInfo;
  UINT8                         RegionCnt = 0;
  UINT32                        DescIndex;
  AMD_MEMORY_RANGE_DESCRIPTOR   *Range;
  BOOLEAN                       MergeRegion;

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

  // Allocate buffer to keep all NVDIMM module SPD data for APCI NFIT table
  AllocateHeapParams.BufferHandle = AMD_MEM_MISC_HANDLES_END - 1;
  AllocateHeapParams.RequestedBufferSize = (sizeof (NVDIMM_SPD_INFO)) * MaxPhysicalDimms;
  AllocateHeapParams.Persist = HEAP_SYSTEM_MEM;
  if (HeapAllocateBuffer (&AllocateHeapParams, StdHeader) != AGESA_SUCCESS) {
    ASSERT (FALSE);
    return AGESA_ERROR;
  }
  nvdimmSpdInfo = (NVDIMM_SPD_INFO *) AllocateHeapParams.BufferPtr;

  IDS_HDT_CONSOLE (MAIN_FLOW, "\tSMBIOS NumSockets = %d\n", NumSockets);
  for (Socket = 0; Socket < NumSockets; Socket ++) {
    SocketScanned[Socket] = FALSE;
  }

  // TYPE 17 entries are organized by physical DIMMs
  NumActiveDimms = 0;
  MaxChannel = 0;
  MaxDimm = 0;
  MaxHandle = 0;
  for (DimmIndex = 0; DimmIndex < MaxPhysicalDimms; DimmIndex ++, PhysicalDimm ++) {
    Socket  = PhysicalDimm->Socket;
    SocketScanned[Socket] = TRUE;
    IDS_HDT_CONSOLE (MAIN_FLOW, "\tSocket %d Scanned\n", Socket);
    TranslateChannelInfo (PhysicalDimm->Channel, &Channel, MemChanXLatTab);
    if (Channel != 0xFF) {
      PhysicalDimm->Channel = Channel;
      if (MaxChannel < Channel) {
        MaxChannel = Channel;
        IDS_HDT_CONSOLE (MAIN_FLOW, "\tMax Channel = %d\n", MaxChannel);
      }
      Dimm    = PhysicalDimm->Dimm;
      if (MaxDimm < Dimm) {
        MaxDimm = Dimm;
        IDS_HDT_CONSOLE (MAIN_FLOW, "\tMax Dimm = %dn", MaxDimm);
      }
      if (MaxHandle < PhysicalDimm->Handle) {
        MaxHandle = PhysicalDimm->Handle;
        IDS_HDT_CONSOLE (MAIN_FLOW, "\tMax Handle = %x\n", MaxHandle);
      }
      nvdimmSpdInfo->Socket = Socket;
      nvdimmSpdInfo->Channel = Channel;
      nvdimmSpdInfo->Dimm = Dimm;
      nvdimmSpdInfo->NvdimmIndex = DimmIndex;   // Fill the DimmIndex no matter it is NVDIMM or not
      // GetPhysicalDimmInfoD4 will move nvdimmSpdInfo to the next available location before return
      IDS_HDT_CONSOLE (MAIN_FLOW, "\tType 17 Entry address = %08x\n", &DmiBuffer->T17[Socket][Channel][Dimm]);
      if (GetPhysicalDimmInfoD4 (&DmiBuffer->T17[Socket][Channel][Dimm], PhysicalDimm, &nvdimmSpdInfo, StdHeader)) {
        NumActiveDimms ++;
      }
      TotalMemSize += (DmiBuffer->T17[Socket][Channel][Dimm].MemorySize != 0x7FFF) ?
                        DmiBuffer->T17[Socket][Channel][Dimm].MemorySize : DmiBuffer->T17[Socket][Channel][Dimm].ExtSize;
    }
  }

  // Create dummy T17 entries for unpopulated sockets
  for (Socket = 0; Socket < NumSockets; Socket ++) {
    if (FALSE == SocketScanned[Socket]) {
      IDS_HDT_CONSOLE (MAIN_FLOW, "\tConstructing Socket %d\n", Socket);
      DummyPhysicalDimm.Socket = Socket;
      DummyPhysicalDimm.DimmPresent = FALSE;
      for (Channel = 0; Channel <= MaxChannel; Channel ++) {
        IDS_HDT_CONSOLE (MAIN_FLOW, "\tConstructing Channel %d\n", Channel);
        DummyPhysicalDimm.Channel = Channel;
        for (Dimm = 0; Dimm <= MaxDimm; Dimm ++) {
          IDS_HDT_CONSOLE (MAIN_FLOW, "\tConstructing Dimm %d\n", Dimm);
          DummyPhysicalDimm.Dimm = Dimm;
          DummyPhysicalDimm.Handle = ++ MaxHandle;
          IDS_HDT_CONSOLE (MAIN_FLOW, "\tDummy Handle = %x\n", DummyPhysicalDimm.Handle);
          IDS_HDT_CONSOLE (MAIN_FLOW, "\tType 17 Entry address = %08x\n", &DmiBuffer->T17[Socket][Channel][Dimm]);
          GetPhysicalDimmInfoD4 (&DmiBuffer->T17[Socket][Channel][Dimm], &DummyPhysicalDimm, &nvdimmSpdInfo, StdHeader);
        }
      }
    }
  }

  // Move nvdimmSpdInfo to the start location before create HOB
  nvdimmSpdInfo = (NVDIMM_SPD_INFO *) AllocateHeapParams.BufferPtr;

  // Create a HOB to publish the nvdimmSpdInfo, the function creating ACPI NFIT will use that
  if (BuildGuidDataHob (&gAmdNvdimmSpdInfoHobGuid, nvdimmSpdInfo, (sizeof (NVDIMM_SPD_INFO)) * MaxPhysicalDimms) == NULL) {
    return EFI_NOT_FOUND;
  }
  // Deallocate heap
  if (HeapDeallocateBuffer ((AMD_MEM_MISC_HANDLES_END - 1), StdHeader) != AGESA_SUCCESS) {
    ASSERT (FALSE);
    return AGESA_ERROR;
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
  if (AmdMemoryInfoHob != NULL) {
    IDS_HDT_CONSOLE (MAIN_FLOW, "BuildT19 AmdMemoryInfoHob->NumberOfDescriptor=%x\n", AmdMemoryInfoHob->NumberOfDescriptor);
    IDS_HDT_CONSOLE (MAIN_FLOW, "\tTotalMemSize=%x\n", TotalMemSize);
    for (DescIndex = 0; DescIndex < AmdMemoryInfoHob->NumberOfDescriptor; DescIndex++) {
      Range = (AMD_MEMORY_RANGE_DESCRIPTOR*)&AmdMemoryInfoHob->Ranges[DescIndex];
      IDS_HDT_CONSOLE (MAIN_FLOW, "\tRange->Attribute=%x\n", Range->Attribute);
      IDS_HDT_CONSOLE (MAIN_FLOW, "\tRange->Base=%16lX\n", Range->Base);
      IDS_HDT_CONSOLE (MAIN_FLOW, "\tRange->Size=%16lX\n", Range->Size);

      MergeRegion = FALSE;
      if ((Range->Attribute == AMD_MEMORY_ATTRIBUTE_AVAILABLE) || (Range->Attribute == AMD_MEMORY_ATTRIBUTE_RESERVED)) {
        if (RegionCnt < MAX_T19_REGION_SUPPORTED) {
          if (RShiftU64(Range->Base, 10) >= 0xFFFFFFFF || RShiftU64(Range->Base + Range->Size, 10) - 1 >= 0xFFFFFFFF) {
            // In Byte
            DmiBuffer->T19[RegionCnt].StartingAddr = 0xFFFFFFFFUL;
            DmiBuffer->T19[RegionCnt].EndingAddr = 0xFFFFFFFFUL;
            DmiBuffer->T19[RegionCnt].ExtStartingAddr = Range->Base;
            DmiBuffer->T19[RegionCnt].ExtEndingAddr   = Range->Base + Range->Size - 1;
            DmiBuffer->T19[RegionCnt].PartitionWidth = NumActiveDimms;
            if (RegionCnt != 0) {
              if (DmiBuffer->T19[RegionCnt-1].ExtEndingAddr + 1 == DmiBuffer->T19[RegionCnt].ExtStartingAddr) {
                IDS_HDT_CONSOLE (MAIN_FLOW, "\tCombine:\n");
                IDS_HDT_CONSOLE (MAIN_FLOW, "\tDmiBuffer->T19[%x].ExtStartingAddr=%16lX\n", RegionCnt-1,  (UINT64)DmiBuffer->T19[RegionCnt-1].ExtStartingAddr);
                IDS_HDT_CONSOLE (MAIN_FLOW, "\tDmiBuffer->T19[%x].ExtEndingAddr=%16lX\n", RegionCnt-1, (UINT64)DmiBuffer->T19[RegionCnt-1].ExtEndingAddr);
                DmiBuffer->T19[RegionCnt-1].ExtEndingAddr = DmiBuffer->T19[RegionCnt].ExtEndingAddr;
                MergeRegion = TRUE;
              }
            }
            IDS_HDT_CONSOLE (MAIN_FLOW, "\tDmiBuffer->T19[%x].ExtStartingAddr=%16lX\n", RegionCnt,  (UINT64)DmiBuffer->T19[RegionCnt].ExtStartingAddr);
            IDS_HDT_CONSOLE (MAIN_FLOW, "\tDmiBuffer->T19[%x].ExtEndingAddr=%16lX\n", RegionCnt, (UINT64)DmiBuffer->T19[RegionCnt].ExtEndingAddr);
          } else {
            // In KByte
            DmiBuffer->T19[RegionCnt].StartingAddr = (UINT32) RShiftU64(Range->Base, 10);
            DmiBuffer->T19[RegionCnt].EndingAddr = (UINT32) RShiftU64(Range->Base + Range->Size, 10) - 1;
            DmiBuffer->T19[RegionCnt].ExtStartingAddr = 0;
            DmiBuffer->T19[RegionCnt].ExtEndingAddr   = 0;
            DmiBuffer->T19[RegionCnt].PartitionWidth = NumActiveDimms;
            if (RegionCnt != 0) {
              if (DmiBuffer->T19[RegionCnt-1].EndingAddr + 1 == DmiBuffer->T19[RegionCnt].StartingAddr) {
                IDS_HDT_CONSOLE (MAIN_FLOW, "\tCombine:\n");
                IDS_HDT_CONSOLE (MAIN_FLOW, "\tDmiBuffer->T19[%x].StartingAddr=%16lX\n", RegionCnt-1,  (UINT64)DmiBuffer->T19[RegionCnt-1].StartingAddr);
                IDS_HDT_CONSOLE (MAIN_FLOW, "\tDmiBuffer->T19[%x].EndingAddr=%16lX\n", RegionCnt-1, (UINT64)DmiBuffer->T19[RegionCnt-1].EndingAddr);
                DmiBuffer->T19[RegionCnt-1].EndingAddr = DmiBuffer->T19[RegionCnt].EndingAddr;
                MergeRegion = TRUE;
              }
            }
            IDS_HDT_CONSOLE (MAIN_FLOW, "\tDmiBuffer->T19[%x].StartingAddr=%08X\n", RegionCnt,  (UINT32)DmiBuffer->T19[RegionCnt].StartingAddr);
            IDS_HDT_CONSOLE (MAIN_FLOW, "\tDmiBuffer->T19[%x].EndingAddr=%08X\n", RegionCnt, (UINT32)DmiBuffer->T19[RegionCnt].EndingAddr);
          }
          if (MergeRegion == TRUE) {
            DmiBuffer->T19[RegionCnt].StartingAddr = 0;
            DmiBuffer->T19[RegionCnt].EndingAddr = 0;
            DmiBuffer->T19[RegionCnt].ExtStartingAddr = 0;
            DmiBuffer->T19[RegionCnt].ExtEndingAddr   = 0;
            DmiBuffer->T19[RegionCnt].PartitionWidth = 0;
            continue;
          }
          RegionCnt++;
        } else {
          IDS_HDT_CONSOLE (MAIN_FLOW, "WARNING!That MAX_T19_REGION_SUPPORTED Size Not Enough!\n");
          break;
        }
      }
    }
  } else {
    IDS_HDT_CONSOLE (MAIN_FLOW, "WARNING!Data AmdMemoryInfoHob Not Ready\n");
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

