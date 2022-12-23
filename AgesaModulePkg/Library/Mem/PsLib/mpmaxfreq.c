/* $NoKeywords:$ */
/**
 * @file
 *
 * mpmaxfreq.c
 *
 * A sub-engine which extracts max. frequency limit value.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Ps)
 * @e \$Revision: 311790 $ @e \$Date: 2015-01-27 13:03:49 +0800 (Tue, 27 Jan 2015) $
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
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "OptionMemory.h"
#include "PlatformMemoryConfiguration.h"
#include "mu.h"
#include "ma.h"
#include "mp.h"
#include "merrhdl.h"
#include "Filecode.h"
CODE_GROUP (G2_PEI)
RDATA_GROUP (G2_PEI)
#define FILECODE LIBRARY_MEM_PSLIB_MPMAXFREQ_FILECODE


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
typedef struct {
  UINT16 Dimms:4;
  UINT16 SR:4;
  UINT16 DR:4;
  UINT16 QR:4;
} CDNMaxFreq;

typedef struct {
  UINT16 Dimms:4;
  UINT16 LR:12;
} CDNLMaxFreq;
/*----------------------------------------------------------------------------
 *                        PROTOTYPES OF LOCAL FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
BOOLEAN
MemPGetMaxFreqSupported (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  );
/* -----------------------------------------------------------------------------*/
/**
 *
 *    A sub-function which extracts the value of max frequency supported from a input table and
 *    compares it with DCTPtr->Timings.TargetSpeed
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *EntryOfTables     - Pointer to MEM_PSC_TABLE_BLOCK
 *
 *     @return          TRUE - Succeed in extracting the table value
 *     @return          FALSE - Fail to extract the table value
 *
 */
BOOLEAN
MemPGetMaxFreqSupported (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  )
{
  UINT8 i;
  UINT8 MaxDimmSlotPerCh;
  UINT8 MaxDimmPerCh;
  UINT8 NOD;
  UINT8 TableSize;
  PSCFG_TYPE Type;
  UINT16 CDN;
  UINT16 MaxFreqSupported;
  UINT16 *SpeedArray;
  UINT8 DDRVoltage;
  UINT8 CurrentVoltage;
  DIMM_TYPE DimmType;
  UINT8 *MotherboardLayerPtr;
  UINT8 MotherboardLayer;
  UINT8 MotherboardPower;
  UINT8 *DqsRoutingTypePtr;
  UINT8 *BypassedDimmSlotsPtr;
  SOC_LOGICAL_ID LogicalCpuid;
  UINT8 PackageType;
  BOOLEAN DisDct;
  UINT8 PsoMaskMaxFreq;
  UINT16 PsoMaskMaxFreq16;
  UINT8 NumDimmSlotInTable;
  UINT16 DimmPopInTable;
  PSCFG_MAXFREQ_ENTRY *TblPtr;
  CH_DEF_STRUCT *CurrentChannel;
  PSC_TBL_ENTRY **TblEntryOfMaxFreq;

  CurrentChannel = NBPtr->ChannelPtr;

  DisDct = FALSE;
  Type = PSCFG_MAXFREQ;
  TblPtr = NULL;
  TableSize = 0;
  PackageType = 0;
  NumDimmSlotInTable = 0;
  DimmPopInTable = 0;
  MotherboardLayer = 0;
  MotherboardPower = 0;
  LogicalCpuid.Family = AMD_FAMILY_UNKNOWN;
  SpeedArray = NULL;

  IDS_HDT_CONSOLE(MEM_FLOW,"\t\tDetermine Max POR Frequency for current DIMM Population...\n");

  MaxDimmPerCh = GetMaxDimmsPerChannel (NBPtr->RefPtr->PlatformMemoryConfiguration, NBPtr->MCTPtr->SocketId, CurrentChannel->ChannelID);
  MaxDimmSlotPerCh = MaxDimmPerCh - GetMaxSolderedDownDimmsPerChannel (NBPtr->RefPtr->PlatformMemoryConfiguration,
                                                                       NBPtr->MCTPtr->SocketId, CurrentChannel->ChannelID);

  if (CurrentChannel->RegDimmPresent != 0) {
    DimmType = RDIMM_TYPE;
  } else if (CurrentChannel->SODimmPresent != 0) {
    DimmType = SODIMM_TYPE;
  } else if (CurrentChannel->LrDimmPresent != 0) {
    DimmType = LRDIMM_TYPE;
  } else {
    DimmType = UDIMM_TYPE;
  }

  // Check if it is "SODIMM plus soldered-down DRAM" or "Soldered-down DRAM only" configuration,
  // DimmType is changed to 'SODWN_SODIMM_TYPE' if soldered-down DRAM exist
  if (MaxDimmSlotPerCh != MaxDimmPerCh) {
    // SODIMM plus soldered-down DRAM
    DimmType = SODWN_SODIMM_TYPE;
  } else if (FindPSOverrideEntry (NBPtr->RefPtr->PlatformMemoryConfiguration, PSO_SOLDERED_DOWN_SODIMM_TYPE, NBPtr->MCTPtr->SocketId, NBPtr->ChannelPtr->ChannelID, 0, NULL, NULL) != NULL) {
    // Soldered-down DRAM only
    DimmType = SODWN_SODIMM_TYPE;
    MaxDimmSlotPerCh = 0;
  }
  if (DimmType != SODWN_SODIMM_TYPE || MaxDimmSlotPerCh != 0) {
    NBPtr->RefPtr->EnableDllPDBypassMode = FALSE;
  }
  NOD = (UINT8) (MaxDimmSlotPerCh != 0) ? (1 << (MaxDimmSlotPerCh - 1)) : _DIMM_NONE;

  BypassedDimmSlotsPtr = FindPSOverrideEntry (NBPtr->RefPtr->PlatformMemoryConfiguration, PSO_BYPASSED_DIMM_SLOTS, NBPtr->MCTPtr->SocketId, NBPtr->ChannelPtr->ChannelID, 0, NULL, NULL);
  if (BypassedDimmSlotsPtr != NULL) {
    NOD -= *BypassedDimmSlotsPtr;
  }

  if (NBPtr->IsSupported[SelectMotherboardLayer]) {
    MotherboardLayerPtr = FindPSOverrideEntry (NBPtr->RefPtr->PlatformMemoryConfiguration, PSO_MOTHER_BOARD_LAYERS, 0, 0, 0, NULL, NULL);
    if (MotherboardLayerPtr != NULL) {
      MotherboardLayer = (1 << *MotherboardLayerPtr);
    }
  }
  if (NBPtr->IsSupported[SelectMotherboardPower]) {
    if (NBPtr->RefPtr->EnableDllPDBypassMode) {
      MotherboardPower = 1;
    } else {
      MotherboardPower = 2;
    }
  }
  DqsRoutingTypePtr = FindPSOverrideEntry (NBPtr->RefPtr->PlatformMemoryConfiguration, PSO_DQS_ROUTING_TYPE, 0, 0, 0, NULL, NULL);
  if (DqsRoutingTypePtr != NULL) {
    NBPtr->DqsRoutingType = *DqsRoutingTypePtr;
  }
  IDS_HDT_CONSOLE(MEM_FLOW,"\t\tDQS Routing Type: %s\n", (DQS_ROUTING_TREE == NBPtr->DqsRoutingType) ? "Tree Routing" : "Daisy Chain");

  TblEntryOfMaxFreq = EntryOfTables->TblEntryOfMaxFreq;
  IDS_OPTION_HOOK (IDS_GET_STRETCH_FREQUENCY_LIMIT, &TblEntryOfMaxFreq, &NBPtr->MemPtr->StdHeader);

  NBPtr->FamilySpecificHook[RelocatePscTblEntryByMotherBoardLayer] (NBPtr, (VOID *) &TblEntryOfMaxFreq);

  i = 0;
  // Obtain table pointer, table size, Logical Cpuid and PSC type according to Dimm, NB and package type.
  while (TblEntryOfMaxFreq[i] != NULL) {
    if (((TblEntryOfMaxFreq[i])->Header.DimmType & DimmType) != 0) {
      if (((TblEntryOfMaxFreq[i])->Header.NumOfDimm & NOD) != 0) {
        if ((TblEntryOfMaxFreq[i])->Header.TechType == CurrentChannel->TechType) {
          if (!NBPtr->IsSupported[SelectMotherboardLayer] || ((TblEntryOfMaxFreq[i])->Header.MotherboardLayer & MotherboardLayer) != 0) {
            if (!NBPtr->IsSupported[SelectMotherboardPower] || ((TblEntryOfMaxFreq[i])->Header.MotherboardPower & MotherboardPower) != 0) {
              if (!NBPtr->IsSupported[DqsRoutingTypeDependence] || ((TblEntryOfMaxFreq[i])->Header.DqsRoutingType & NBPtr->DqsRoutingType) != 0) {
                //
                // Determine if this is the expected NB Type
                //
                LogicalCpuid = (TblEntryOfMaxFreq[i])->Header.LogicalCpuid;
                PackageType = (TblEntryOfMaxFreq[i])->Header.PackageType;
                if (MemPIsIdSupported (NBPtr, LogicalCpuid, PackageType)) {
                  TblPtr = (PSCFG_MAXFREQ_ENTRY *) ((TblEntryOfMaxFreq[i])->TBLPtr);
                  TableSize = (TblEntryOfMaxFreq[i])->TableSize;
                  Type = (TblEntryOfMaxFreq[i])->Header.PSCType;
                  break;
                }
              }
            }
          }
        }
      }
    }
    i++;
  }

  // Check whether no table entry is found.
  if (TblEntryOfMaxFreq[i] == NULL) {
    IDS_HDT_CONSOLE(MEM_FLOW, "\t\tNo Max Frequency Table Found.");
    return FALSE;
  }

  MaxFreqSupported = UNSUPPORTED_DDR_FREQUENCY;
  CDN = 0;
  DDRVoltage = (UINT8) CONVERT_VDDIO_TO_ENCODED (NBPtr->RefPtr->DDRVoltage, CurrentChannel->TechType);
  IDS_HDT_CONSOLE(MEM_FLOW, "\t\tVoltage Index = %d\n",DDRVoltage);
  // Construct the condition value
  ((CDNMaxFreq *)&CDN)->Dimms = CurrentChannel->Dimms;
  if (Type == PSCFG_MAXFREQ) {
    for (i = 0; i < MAX_DIMMS_PER_CHANNEL; i++) {
      if ((CurrentChannel->DimmSRPresent & (UINT8) (1 << i)) != 0) {
        ((CDNMaxFreq *)&CDN)->SR += 1;
      }
      if ((CurrentChannel->DimmDrPresent & (UINT16) (1 << i)) != 0) {
        ((CDNMaxFreq *)&CDN)->DR += 1;
      }
      if ((CurrentChannel->DimmQrPresent & (UINT16) (1 << i)) != 0) {
        if (i < 2) {
          ((CDNMaxFreq *)&CDN)->QR += 1;
        }
      }
    }
  } else {
    ((CDNLMaxFreq *)&CDN)->LR = CurrentChannel->Dimms;
  }
  IDS_HDT_CONSOLE(MEM_FLOW,"\t\t\t          NumDimmSlots   Dimms     SR     DR     QR    Speed[0],   Speed[1],   Speed[2]\n");
  IDS_HDT_CONSOLE(MEM_FLOW,"\n\t\t Current ->      %d           %d        %x      %x      %x\n",
    NOD, ((CDNMaxFreq *)&CDN)->Dimms, ((CDNMaxFreq *)&CDN)->SR, ((CDNMaxFreq *)&CDN)->DR, ((CDNMaxFreq *)&CDN)->QR   );

  for (i = 0; i < TableSize; i++) {
    NumDimmSlotInTable = TblPtr->MAXFREQ_ENTRY.DimmSlotPerCh;
    DimmPopInTable = (Type == PSCFG_MAXFREQ) ? TblPtr->MAXFREQ_ENTRY.CDN : ((PSCFG_LR_MAXFREQ_ENTRY *)TblPtr)->LR_MAXFREQ_ENTRY.CDN;
    IDS_HDT_CONSOLE(MEM_FLOW,"\t\t\t    %d          %d           %d        %x      %x      %x     %d        %d        %d\n",
      i, NumDimmSlotInTable, TblPtr->_MAXFREQ_ENTRY.Dimms, TblPtr->_MAXFREQ_ENTRY.SR, TblPtr->_MAXFREQ_ENTRY.DR, TblPtr->_MAXFREQ_ENTRY.QR,
      TblPtr->MAXFREQ_ENTRY.Speed[0], TblPtr->MAXFREQ_ENTRY.Speed[1], TblPtr->MAXFREQ_ENTRY.Speed[2]);
    if (((NumDimmSlotInTable & NOD) != 0) && (CDN == DimmPopInTable)) {
      if (Type == PSCFG_MAXFREQ) {
        SpeedArray = TblPtr->MAXFREQ_ENTRY.Speed;
      } else {
        SpeedArray = ((PSCFG_LR_MAXFREQ_ENTRY *)TblPtr)->LR_MAXFREQ_ENTRY.Speed;
      }
      break;
    }
    TblPtr++;
  }

  PsoMaskMaxFreq16 = MemPProceedTblDrvOverride (NBPtr, NBPtr->RefPtr->PlatformMemoryConfiguration, PSO_TBLDRV_SPEEDLIMIT);
  if ((PsoMaskMaxFreq16 & INVALID_CONFIG_FLAG) == 0) {
    PsoMaskMaxFreq = (UINT8) PsoMaskMaxFreq16;
    if (PsoMaskMaxFreq != 0) {
      SpeedArray = NBPtr->PsPtr->SpeedLimit;
    }
  } else {
    SpeedArray = NULL;
  }

  if (SpeedArray != NULL) {
    if (NBPtr->SharedPtr->VoltageMap != VDDIO_DETERMINED) {
      IDS_HDT_CONSOLE (MEM_FLOW, "\n\t\t\tCheck speed supported for each VDDIO for Node%d DCT%d: ", NBPtr->Node, NBPtr->Dct);
      for (CurrentVoltage = VOLT_STARTING_ENCODED_VAL; CurrentVoltage <= GET_ENCODED_VOLTAGE_LIMIT (CurrentChannel->TechType) ; CurrentVoltage ++) {
        if (NBPtr->SharedPtr->VoltageMap & (1 << CurrentVoltage)) {
          IDS_HDT_CONSOLE (MEM_FLOW, "%s -> %dMHz ", GET_ENCODED_VDDIO_STRING(CurrentVoltage, CurrentChannel->TechType), SpeedArray[CurrentVoltage]);
          if (NBPtr->DCTPtr->Timings.TargetSpeed > SpeedArray[CurrentVoltage]) {
            MaxFreqSupported = SpeedArray[CurrentVoltage];
          } else {
            MaxFreqSupported = NBPtr->DCTPtr->Timings.TargetSpeed;
          }
          if (NBPtr->MaxFreqVDDIO[CurrentVoltage] > MaxFreqSupported) {
            NBPtr->MaxFreqVDDIO[CurrentVoltage] = MaxFreqSupported;
          }
        } else {
          NBPtr->MaxFreqVDDIO[CurrentVoltage] = 0;
        }
      }
      IDS_HDT_CONSOLE (MEM_FLOW, "\n");
    }
    ASSERT (DDRVoltage < GET_ENCODED_VOLTAGE_LIMIT (CurrentChannel->TechType));
    for (CurrentVoltage = DDRVoltage; CurrentVoltage != VOLT_UNSUPPORTED_ENCODED_VAL; CurrentVoltage --) {
      if (NBPtr->SharedPtr->VoltageMap & (1 << CurrentVoltage)) {
        MaxFreqSupported = SpeedArray[CurrentVoltage];
        if (MaxFreqSupported != UNSUPPORTED_DDR_FREQUENCY) {
          NBPtr->RefPtr->DDRVoltage = CONVERT_ENCODED_TO_VDDIO (CurrentVoltage, CurrentChannel->TechType);
          IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tVDDIO leveraged to %s\n", GET_ENCODED_VDDIO_STRING(CurrentVoltage, CurrentChannel->TechType));
          IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tMax Frequency supported is %d\n", MaxFreqSupported);
          break;
        }
      }
    }
  }

  if (MaxFreqSupported == UNSUPPORTED_DDR_FREQUENCY) {
    // No entry in the table for current dimm population is found
    IDS_HDT_CONSOLE (MEM_FLOW, "\nDCT %d: No entry is found in the Max Frequency table\n", NBPtr->Dct);
    DisDct = TRUE;
  } else if (MaxFreqSupported != 0) {
    if ((NBPtr->DCTPtr->Timings.TargetSpeed > MaxFreqSupported) && !NBPtr->IsSupported[AMPIsEnabled]) {
      NBPtr->DCTPtr->Timings.TargetSpeed = MaxFreqSupported;
    }
  } else if (NBPtr->SharedPtr->VoltageMap == VDDIO_DETERMINED) {
    // Dimm population is not supported at current voltage
    // Also if there is no performance optimization, disable the DCT
    DisDct = TRUE;
  }

  if (DisDct) {
    NBPtr->DCTPtr->Timings.DimmExclude |= NBPtr->DCTPtr->Timings.DctDimmValid;
    PutEventLog (AGESA_ERROR, MEM_ERROR_UNSUPPORTED_DIMM_CONFIG, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
    SetMemError (AGESA_ERROR, NBPtr->MCTPtr);
    // Change target speed to highest value so it won't affect other channels when leveling frequency across the node.
    NBPtr->DCTPtr->Timings.TargetSpeed = UNSUPPORTED_DDR_FREQUENCY;
  }

  return TRUE;
}

