/* $NoKeywords:$ */
/**
 * @file
 *
 * mfDMID4.c
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
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "Library/AmdHeapLib.h"
#include "mm.h"
#include "mn.h"
#include "mu.h"
#include "mtspd4.h"
#include "Library/AmdMemDmiLib.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)

#define FILECODE LIBRARY_MEM_FEATDMICOLLECTLIB_AMDMEMDMID4LIB_FILECODE
/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */

#define MAX_DCTS_PER_DIE 2

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

BOOLEAN
MemFDMISupport4 (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  );

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *  This function gets DDR4 DMI information from SPD buffer and stores the info into heap
 *
 *     @param[in,out]   *MemMainPtr   - Pointer to the MEM_MAIN_DATA_BLOCK
 *
 */
BOOLEAN
MemFDMISupport4 (
  IN OUT   MEM_MAIN_DATA_BLOCK *MemMainPtr
  )
{
  UINT8  i;
  UINT8  Dimm;
  UINT8  Socket;
  UINT8  NodeId;
  UINT8  Dct;
  UINT8  Channel;
  UINT8  temp;
  UINT16 LocalHandle;
  UINT8  MaxPhysicalDimms;
  UINT8  MaxLogicalDimms;
  UINT8  NumLogicalDimms;
  UINT32 EccCapable;
  UINT32 *TotalMemSizePtr;
  UINT8  *DmiTable;
  UINT8  MaxChannelsPerSocket;
  UINT8  MaxDimmsPerChannel;
  UINT8  FormFactor;
  UINT16 TotalWidth;
  UINT16 Capacity;
  UINT16 Width;
  UINT8  Rank;
  UINT16 BusWidth;
  UINT64 ManufacturerIdCode;
  UINT32 MaxSockets;
  UINT32 Address;
  UINT8  ChipSelectPairScale;
  UINT32 TotalSize;
  UINT32 DimmSize;
  UINT32 CsBaseAddrReg0;
  UINT32 CsBaseAddrReg1;
  UINT64 AddrValue;
  UINT64 DctMemBase;
  UINT64 NodeMemBase;
  UINT64 SysMemSize;
  INT32  MTB_ps;
  INT32  FTB_ps;
  INT32  Value32;
  UINT8  VoltageMap;
  BOOLEAN DctInterleaveEnabled;
  UINT64  DctInterleavedMemSize;
  BOOLEAN NodeInterleaveEnabled;
  UINT16 T17HandleMatrix[MAX_SOCKETS_SUPPORTED][MAX_CHANNELS_PER_SOCKET][MAX_DIMMS_PER_CHANNEL];

  MEM_NB_BLOCK  *NBPtr;
  MEM_PARAMETER_STRUCT *RefPtr;
  MEM_DATA_STRUCT *MemPtr;
  DIE_STRUCT *MCTPtr;
  CH_DEF_STRUCT *ChannelPtr;
  SPD_DEF_STRUCT *SpdDataStructure;
  ALLOCATE_HEAP_PARAMS AllocHeapParams;
  MEM_DMI_PHYSICAL_DIMM_INFO *DmiPhysicalDimmInfoTable;
  MEM_DMI_LOGICAL_DIMM_INFO *DmiLogicalDimmInfoTable;
  DMI_T17_MEMORY_TYPE *DmiType17MemTypePtr;

  NBPtr = MemMainPtr->NBPtr;
  MemPtr = MemMainPtr->MemPtr;
  SpdDataStructure = MemPtr->SpdDataStructure;
  MCTPtr = NBPtr->MCTPtr;
  RefPtr = MemPtr->ParameterListPtr;

  // Initialize local variables
  LocalHandle = 1;
  MaxPhysicalDimms = 0;
  MaxLogicalDimms = 0;
  NumLogicalDimms = 0;
  TotalSize = 0;
  NodeMemBase = 0;
  SysMemSize = 0;

  AGESA_TESTPOINT (TpProcMemDmi, &MemPtr->StdHeader);

  ASSERT (NBPtr != NULL);

  MaxSockets = (UINT8) (0x000000FF & GetPlatformNumberOfSockets ());
  for (Socket = 0; Socket < MaxSockets; Socket++) {
    for (Channel = 0; Channel < GetMaxChannelsPerSocket (RefPtr->PlatformMemoryConfiguration, Socket, &MemPtr->StdHeader); Channel++) {
      temp = (UINT8) GetMaxDimmsPerChannel (RefPtr->PlatformMemoryConfiguration, Socket, Channel);
      MaxPhysicalDimms = MaxPhysicalDimms + temp;
      MaxLogicalDimms += MAX_DIMMS_PER_CHANNEL;
    }
  }

  // Allocate heap for memory DMI table 16, 17, 19, 20
  AllocHeapParams.RequestedBufferSize = sizeof (UINT8) +                                       // Storage for MaxPhysicalDimms
                                        sizeof (UINT8) +                                       // Storage for Type Detail
                                        sizeof (UINT32) +                                      // Storage for Total Memory Size
                                        sizeof (UINT32) +                                      // Storage for ECC Type
                                        sizeof (DMI_T17_MEMORY_TYPE) +
                                        MaxPhysicalDimms * sizeof (MEM_DMI_PHYSICAL_DIMM_INFO) +
                                        sizeof (UINT8) +                                       // Storage for MaxLogicalDimms
                                        MaxLogicalDimms * sizeof (MEM_DMI_LOGICAL_DIMM_INFO);

  AllocHeapParams.BufferHandle = AMD_DMI_MEM_DEV_INFO_HANDLE;
  AllocHeapParams.Persist = HEAP_SYSTEM_MEM;
  if (AGESA_SUCCESS != HeapAllocateBuffer (&AllocHeapParams, &MemPtr->StdHeader)) {
    PutEventLog (AGESA_CRITICAL, MEM_ERROR_HEAP_ALLOCATE_FOR_DMI_TABLE_DDR4, NBPtr->Node, 0, 0, 0, &MemPtr->StdHeader);
    SetMemError (AGESA_CRITICAL, MCTPtr);
    // Could not allocate heap for memory DMI table 16,17,19 and 20 for DDR4
    ASSERT (FALSE);
    return FALSE;
  }

  DmiTable = (UINT8 *) AllocHeapParams.BufferPtr;
  // Max number of physical DIMMs
  *DmiTable = MaxPhysicalDimms;
  DmiTable ++;
  // Type Detail;
  *DmiTable = 0;
  DmiTable ++;
  // Pointer to total memory size
  TotalMemSizePtr = (UINT32 *) DmiTable;
  DmiTable += sizeof (UINT32);
  // Ecc Type
  EccCapable = NBPtr->GetBitField (NBPtr, BFEccCapable);
  *((UINT32 *)DmiTable) = EccCapable;
  DmiTable += sizeof (UINT32);
  // Memory Type
  DmiType17MemTypePtr = (DMI_T17_MEMORY_TYPE *) DmiTable;
  *DmiType17MemTypePtr = Ddr4MemType;
  DmiType17MemTypePtr ++;
  DmiTable = (UINT8 *) DmiType17MemTypePtr;
  // Pointer to DMI info of Physical DIMMs
  DmiPhysicalDimmInfoTable = (MEM_DMI_PHYSICAL_DIMM_INFO *) DmiTable;

  //
  // Gather physical DIMM DMI info
  //
  for (Socket = 0; Socket < MaxSockets; Socket ++) {
    MaxChannelsPerSocket = GetMaxChannelsPerSocket (RefPtr->PlatformMemoryConfiguration, Socket, &MemPtr->StdHeader);
    DctMemBase = 0;
    for (Channel = 0; Channel < MaxChannelsPerSocket; Channel ++) {
      //
      // Get Node number and Dct number for this channel
      //
      ChannelPtr = MemPtr->SocketList[Socket].ChannelPtr[Channel];
      NodeId = ChannelPtr->MCTPtr->NodeId;
      NBPtr = MemMainPtr->NBPtr;
      Dct = ChannelPtr->Dct;
      NBPtr = &NBPtr[NodeId];
      NBPtr->SwitchDCT (NBPtr, Dct);

      MaxDimmsPerChannel = GetMaxDimmsPerChannel (RefPtr->PlatformMemoryConfiguration, Socket, Channel);
      for (Dimm = 0; Dimm < MaxDimmsPerChannel; Dimm ++, SpdDataStructure ++, LocalHandle++) {
        //
        // Initialize default value for DMI fields
        //
        DmiPhysicalDimmInfoTable->DimmPresent = 0;
        DmiPhysicalDimmInfoTable->Socket = Socket;
        DmiPhysicalDimmInfoTable->Channel = Channel;
        DmiPhysicalDimmInfoTable->Dimm = Dimm;
        DmiPhysicalDimmInfoTable->TotalWidth = 0xFFFF;
        DmiPhysicalDimmInfoTable->DataWidth = 0xFFFF;
        DmiPhysicalDimmInfoTable->MemorySize = 0;
        DmiPhysicalDimmInfoTable->Speed = 0;
        DmiPhysicalDimmInfoTable->ManufacturerIdCode = 0;
        DmiPhysicalDimmInfoTable->Attributes = 0;
        DmiPhysicalDimmInfoTable->ConfigSpeed = 0;
        DmiPhysicalDimmInfoTable->ExtSize = 0;
        DmiPhysicalDimmInfoTable->FormFactor = UnknowFormFactor;
        DmiPhysicalDimmInfoTable->Handle = LocalHandle;
        T17HandleMatrix[Socket][Channel][Dimm] = LocalHandle;

        for (i = 0; i < sizeof (DmiPhysicalDimmInfoTable->SerialNumber); i++) {
          DmiPhysicalDimmInfoTable->SerialNumber[i] = 0xFF;
        }

        for (i = 0; i < sizeof (DmiPhysicalDimmInfoTable->PartNumber); i++) {
          DmiPhysicalDimmInfoTable->PartNumber[i] = 0x0;
        }
        //
        // Data Width and Total Width
        //
        if (SpdDataStructure->DimmPresent) {
          switch (SpdDataStructure->Data[SPD_BUS_WIDTH] & BUSWIDTH_MASK) {
          case 0:
            BusWidth = 8;           // 8 bits
            break;
          case 1:
            BusWidth  = 16;         // 16 bits
            break;
          case 2:
            BusWidth  = 32;         // 32 bits
            break;
          case 3:
            BusWidth  = 64;         // 64 bits
            break;
          default:
            BusWidth = 0;
            ASSERT (FALSE);
          }
          DmiPhysicalDimmInfoTable->DataWidth = BusWidth;
          TotalWidth = BusWidth;
          if ((SpdDataStructure->Data[SPD_BUSWIDTH_EXT] & BUSWIDTH_EXT_ECC) != 0) {
            TotalWidth = TotalWidth + 8;
          }
          DmiPhysicalDimmInfoTable->TotalWidth = TotalWidth;
          //
          // Memory Size (offset 0Ch)
          //
          Capacity = 0;
          Width = 0;
          Rank = 0;
          // Capacity
          temp = (UINT8) (SpdDataStructure->Data[SPD_CAPACITY] & CAPACITY_MASK);
          if (temp < 8) {
            Capacity = 0x100 << temp;
          } else {
            // Reserved Value
            Capacity = 0;
          }
          // Device Width
          temp = (UINT8) (SpdDataStructure->Data[SPD_DEVICE_WIDTH] & DEVICE_WIDTH_MASK);
          if (temp < 4) {
            Width = 4 << temp;
          } else {
            // Reserved value
            Width = 0;
          }
          // Rank
          temp = (UINT8) ((SpdDataStructure->Data[SPD_RANKS] >> RANKS_SHIFT) & RANKS_MASK);
          if ( temp < 4) {
            Rank = temp + 1;
          } else {
            // Reserved value
            Rank = 0;
          }
          DmiPhysicalDimmInfoTable->Attributes = Rank;

          DimmSize = (UINT32) (Capacity / 8 * BusWidth / Width * Rank);
          if (DimmSize < 0x7FFF) {
            DmiPhysicalDimmInfoTable->MemorySize = (UINT16) DimmSize;
          } else {
            DmiPhysicalDimmInfoTable->MemorySize = 0x7FFF;
            DmiPhysicalDimmInfoTable->ExtSize = DimmSize;
          }
          //
          // Form Factor (offset 0Eh)
          //
          FormFactor = (UINT8) (SpdDataStructure->Data[SPD_BASE_MODULE_TYPE] & MODULE_TYPE_MASK);
          switch (FormFactor) {
          case 0x01:    // RDIMM
          case 0x02:    // UDIMM
          case 0x04:    // LRDIMM
            DmiPhysicalDimmInfoTable->FormFactor = 0x09;         // RDIMM or UDIMM or LRDIMM
            break;
          case 0x03:    // SO-DIMM
          case 0x08:    // 72b-SO-RDIMM
          case 0x09:    // 72b-SO-UDIMM
          case 0x0A:    // 16b-SO-DIMM
          case 0x0B:    // 32b-SO-DIMM
            DmiPhysicalDimmInfoTable->FormFactor = 0x0D;         // SO-DIMM
            break;
          default:
            DmiPhysicalDimmInfoTable->FormFactor = 0x02;         // UNKNOWN
          }
          //
          // DIMM Present
          //
          DmiPhysicalDimmInfoTable->DimmPresent = 1;
          //
          // Type Detail (offset 13h)
          //
          /// @todo Review this field it's programming is suspect.
          if (((FormFactor & 0x0F) == 0x01) || ((FormFactor & 0x0F) == 0x04)) {
            *((UINT8 *) (AllocHeapParams.BufferPtr) + 1) = 1;      // Registered (Buffered)
          } else {
            *((UINT8 *) (AllocHeapParams.BufferPtr) + 1) = 2;      // Unbuffered (Unregistered)
          }
          //
          // Speed (offset 15h)
          //
          MTB_ps = (((SpdDataStructure->Data[SPD_MEDIUM_TIMEBASE] >> MTB_SHIFT) & MTB_MSK) == 0) ? 125 : 0;
          FTB_ps = ((SpdDataStructure->Data[SPD_FINE_TIMEBASE] & FTB_MSK) == 0) ? 1 : 0;

          Value32 = (MTB_ps * SpdDataStructure->Data[SPD_TCK]) + (FTB_ps * (INT8) SpdDataStructure->Data[SPD_TCK_FTB]) ;
          if (Value32 <= 834) {
            DmiPhysicalDimmInfoTable->Speed = 1200;              // DDR3-2400
          } else if (Value32 <= 938) {
            DmiPhysicalDimmInfoTable->Speed = 1067;              // DDR3-2133
          } else if (Value32 <= 1071) {
            DmiPhysicalDimmInfoTable->Speed = 933;               // DDR3-1866
          } else if (Value32 <= 1250) {
            DmiPhysicalDimmInfoTable->Speed = 800;               // DDR3-1600
          } else if (Value32 <= 1500) {
            DmiPhysicalDimmInfoTable->Speed = 667;               // DDR3-1333
          } else if (Value32 <= 1875) {
            DmiPhysicalDimmInfoTable->Speed = 533;               // DDR3-1066
          } else if (Value32 <= 2500) {
            DmiPhysicalDimmInfoTable->Speed = 400;               // DDR3-800
          }
          //
          // Manufacturer (offset 17h)
          //
          ManufacturerIdCode = (UINT64) SpdDataStructure->Data[SPD_MANUFACTURER_ID_MSB];
          DmiPhysicalDimmInfoTable->ManufacturerIdCode = (ManufacturerIdCode << 8) | ((UINT64) SpdDataStructure->Data[SPD_MANUFACTURER_ID_LSB]);

          // Serial Number (offset 18h)
          for (i = 0; i < 8; i++) {
            DmiPhysicalDimmInfoTable->SerialNumber[i] = (UINT8) SpdDataStructure->Data[i + SPD_SERIAL_NUMBER];
          }
          // // Part Number (offset 1Ah)
          for (i = 0; i < 20; i++) {
            DmiPhysicalDimmInfoTable->PartNumber[i] = (UINT8) SpdDataStructure->Data[i + SPD_PART_NUMBER];
          }

          // Configured Memory Clock Speed (offset 20h)
          DmiPhysicalDimmInfoTable->ConfigSpeed = NBPtr->DCTPtr->Timings.Speed;
          //
          VoltageMap = (UINT8) (SpdDataStructure->Data[6] ^ 1);
          DmiPhysicalDimmInfoTable->MinimumVoltage = CONVERT_ENCODED_TO_VDDIO_MILLIVOLTS (HighBitSet32 (VoltageMap), DDR4_TECHNOLOGY);
          DmiPhysicalDimmInfoTable->MaximumVoltage = CONVERT_ENCODED_TO_VDDIO_MILLIVOLTS (LowBitSet32 (VoltageMap), DDR4_TECHNOLOGY);
          switch (NBPtr->RefPtr->DDRVoltage) {
          case VOLT1_2:
            DmiPhysicalDimmInfoTable->ConfiguredVoltage = 1200;
            break;
          case VOLT_TBD1:
            DmiPhysicalDimmInfoTable->ConfiguredVoltage = 1200;
            break;
          case VOLT_TBD2:
            DmiPhysicalDimmInfoTable->ConfiguredVoltage = 1200;
            break;
          default:
            DmiPhysicalDimmInfoTable->ConfiguredVoltage = 1200;
            break;
          }
        }  // Dimm present
        TotalSize += (UINT32) DmiPhysicalDimmInfoTable->MemorySize;
        DmiPhysicalDimmInfoTable ++;
      }    // Dimm loop
    }      // Channel loop
  }        // Socket loop
  //
  // Max number of logical DIMMs
  //
  DmiTable = (UINT8 *) DmiPhysicalDimmInfoTable;
  *DmiTable = MaxLogicalDimms;
  DmiTable ++;
  //
  // Pointer to DMI info of Logical DIMMs
  //
  DmiLogicalDimmInfoTable = (MEM_DMI_LOGICAL_DIMM_INFO *) DmiTable;
  //
  // Calculate the total memory size in the system
  //
  SysMemSize = MemFGetNodeMemBase (MemMainPtr->NBPtr, MemPtr->DieCount);
  //
  // Gather logical DIMM DMI info
  //
  for (Socket = 0; Socket < MaxSockets; Socket ++) {
    MaxChannelsPerSocket = GetMaxChannelsPerSocket (RefPtr->PlatformMemoryConfiguration, Socket, &MemPtr->StdHeader);
    DctMemBase = 0;
    for (Channel = 0; Channel < MaxChannelsPerSocket; Channel ++) {
      MaxDimmsPerChannel = GetMaxDimmsPerChannel (RefPtr->PlatformMemoryConfiguration, Socket, Channel);
      //
      // Get Node number and Dct number for this channel
      //
      ChannelPtr = MemPtr->SocketList[Socket].ChannelPtr[Channel];
      NodeId = ChannelPtr->MCTPtr->NodeId;
      NBPtr = MemMainPtr->NBPtr;
      Dct = ChannelPtr->Dct;
      NodeMemBase = MemFGetNodeMemBase (NBPtr, NodeId);
      NBPtr = &NBPtr[NodeId];

      DctMemBase = MemFGetDctMemBase (NBPtr, Dct);
      DctInterleavedMemSize = MemFGetDctInterleavedMemSize (NBPtr);
      NBPtr->SwitchDCT (NBPtr, Dct);
      NodeInterleaveEnabled = (NBPtr->GetBitField (NBPtr, BFDramIntlvEn) == 0) ? FALSE : TRUE;
      DctInterleaveEnabled = (NBPtr->GetBitField (NBPtr, BFDctSelIntLvEn) == 0) ? FALSE : TRUE;

      for (Dimm = 0; Dimm < MAX_DIMMS_PER_CHANNEL; Dimm ++, DmiLogicalDimmInfoTable ++) {
        //
        // Initialize default value for DMI fields
        //
        DmiLogicalDimmInfoTable->DimmPresent = 0;
        DmiLogicalDimmInfoTable->Socket = Socket;
        DmiLogicalDimmInfoTable->Channel = Channel;
        DmiLogicalDimmInfoTable->Dimm = Dimm;
        DmiLogicalDimmInfoTable->Interleaved = FALSE;
        DmiLogicalDimmInfoTable->StartingAddr = 0;
        DmiLogicalDimmInfoTable->EndingAddr = 0;
        DmiLogicalDimmInfoTable->ExtStartingAddr = 0;
        DmiLogicalDimmInfoTable->ExtEndingAddr = 0;
        //
        // Starting/Ending Address for each DIMM
        //
        // If Ending Address >= 0xFFFFFFFF, update Starting Address & Ending Address to 0xFFFFFFFF,
        // and use the Extended Starting Address & Extended Ending Address instead.
        //
        CsBaseAddrReg0 = NBPtr->GetBitField (NBPtr, BFCSBaseAddr0Reg + 2 * Dimm);
        CsBaseAddrReg1 = NBPtr->GetBitField (NBPtr, BFCSBaseAddr0Reg + 2 * Dimm + 1);
        if ((CsBaseAddrReg0 & 1) != 0 || (CsBaseAddrReg1 & 1) != 0) {
          ASSERT (NumLogicalDimms < MaxLogicalDimms);
          NumLogicalDimms ++;
          DmiLogicalDimmInfoTable->DimmPresent = 1;
          if (Dimm < MaxDimmsPerChannel) {
            // The logical DIMM is mapped from a SR/QR physical DIMM
            DmiLogicalDimmInfoTable->MemoryDeviceHandle = T17HandleMatrix[Socket][Channel][Dimm];
          } else {
            // The logical DIMM is mapped from a QR physical DIMM
            DmiLogicalDimmInfoTable->MemoryDeviceHandle = T17HandleMatrix[Socket][Channel][Dimm - 2];
          }
          //
          // For DR and QR DIMMs,  DIMM size should be scaled based on the CS pair presence
          //
          ChipSelectPairScale = ((CsBaseAddrReg0 & 1) != 0 && (CsBaseAddrReg1 & 1) != 0) ? 1 : 0;
          Address = ((CsBaseAddrReg0 & 1) != 0 ? CsBaseAddrReg0 : CsBaseAddrReg1) & NBPtr->CsRegMsk;
          Address = (Address & 0xFFFF0000) >> 2;
          if (DctInterleaveEnabled) {
            //
            // When channel interleaving is enabled, all the DIMMs on the node share the same starting address
            //
            Address = (UINT32)NodeMemBase;
            DmiLogicalDimmInfoTable->Interleaved = TRUE;
          } else {
            if (NBPtr->DCTPtr->BkIntDis == FALSE && NBPtr->RefPtr->EnableBankIntlv == TRUE) {
              //
              // When bank interleaving is enabled, all the chip selects share the same starting address
              //
              Address = (UINT32) (NodeMemBase + DctMemBase);
              DmiLogicalDimmInfoTable->Interleaved = TRUE;
            } else {
              Address += (UINT32) (NodeMemBase + DctMemBase);
            }
          }
          if (NodeInterleaveEnabled) {
            //
            // When node interleaving is enabled, all the DIMMs in the system share the same starting address
            //
            Address = 0;
            DmiLogicalDimmInfoTable->Interleaved = TRUE;
          }
          DmiLogicalDimmInfoTable->StartingAddr = Address;
          AddrValue = (UINT64) Address +
                      RShiftU64 ((UINT64) ((NBPtr->GetBitField (NBPtr, BFCSMask0Reg + Dimm) & 0xFFFF0000) + 0x00080000),
                      (2 - ChipSelectPairScale) ) - 1;
          if (NBPtr->DCTPtr->BkIntDis == FALSE && NBPtr->RefPtr->EnableBankIntlv == TRUE) {
            //
            // When bank interleaving is enabled, all the chip selects share the same ending address
            //
            AddrValue = NodeMemBase + DctMemBase + (NBPtr->DCTPtr->Timings.DctMemSize << 6) - 1;
          }
          if (DctInterleaveEnabled) {
            //
            // When channel interleaving is enabled, the interleaved range is accounted for in the ending address of each DCT
            //
            AddrValue = NodeMemBase + MemFGetDctInterleavedLimit (NBPtr, Dct, DctMemBase, DctInterleavedMemSize);
          }
          if (NodeInterleaveEnabled) {
            //
            // When node interleaving is enabled, all the DIMMs in the system share the same ending address
            //
            AddrValue = SysMemSize - 1;
          }
          if (AddrValue >= ((UINT64) 0xFFFFFFFF)) {
            DmiLogicalDimmInfoTable->StartingAddr = 0xFFFFFFFFUL;
            DmiLogicalDimmInfoTable->EndingAddr = 0xFFFFFFFFUL;
            DmiLogicalDimmInfoTable->ExtStartingAddr = (UINT64) Address;
            DmiLogicalDimmInfoTable->ExtEndingAddr = AddrValue;
          } else {
            DmiLogicalDimmInfoTable->EndingAddr = (UINT32) AddrValue;
          }
        }
      }    // Dimm loop
    }      // Channel loop
  }        // Socket loop

  // Max Capacity
  *TotalMemSizePtr = TotalSize;
  IDS_HDT_CONSOLE(MEM_FLOW, "DMI Total Memory Size: %08X\n", *TotalMemSizePtr);

  return TRUE;
}


/*---------------------------------------------------------------------------------------
 *                          L O C A L    F U N C T I O N S
 *---------------------------------------------------------------------------------------
 */

