/* $NoKeywords:$ */
/**
 * @file
 *
 * mpsao.c
 *
 * A sub-engine which extracts Slow access mode, Address timing and Output driver compensation value.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Ps)
 * @e \$Revision: 322133 $ @e \$Date: 2015-07-07 20:04:05 +0800 (Tue, 07 Jul 2015) $
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

#define FILECODE LIBRARY_MEM_PSLIB_MPSAO_FILECODE


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
/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */
BOOLEAN
MemPGetSAO (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  );
/* -----------------------------------------------------------------------------*/
/**
 *
 *    A sub-function which extracts Slow mode, Address timing and Output driver compensation value
 *    from a input table and store those value to a specific address.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *EntryOfTables     - Pointer to MEM_PSC_TABLE_BLOCK
 *
 *     @return          TRUE - Table values can be extracted per dimm population and ranks type.
 *     @return          FALSE - Table values cannot be extracted per dimm population and ranks type.
 *
 */
BOOLEAN
MemPGetSAO (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  )
{

  UINT8 i;
  UINT8 MaxDimmPerCh;
  UINT8 MaxDimmSlotPerCh;
  UINT8 NOD;
  UINT8 TableSize;
  UINT32 CurDDRrate;
  UINT8 DDRVoltage;
  UINT16 RankTypeOfPopulatedDimm;
  UINT16 RankTypeInTable;
  UINT8 PsoMaskSAO;
  DIMM_TYPE DimmType;
  UINT8 *MotherboardLayerPtr;
  UINT8 MotherboardLayer;
  UINT8 MotherboardPower;
  UINT8 *DqsRoutingTypePtr;
  SOC_LOGICAL_ID LogicalCpuid;
  UINT8 PackageType;
  PSCFG_SAO_ENTRY *TblPtr;
  CH_DEF_STRUCT *CurrentChannel;

  CurrentChannel = NBPtr->ChannelPtr;

  TblPtr = NULL;
  MotherboardLayer = 0;
  MotherboardPower = 0;
  TableSize = 0;
  PackageType = 0;
  LogicalCpuid.Family = AMD_FAMILY_UNKNOWN;

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

  i = 0;
  // Obtain table pointer, table size, Logical Cpuid and PSC type according to Dimm, NB and package type.
  while (EntryOfTables->TblEntryOfSAO[i] != NULL) {
    if (((EntryOfTables->TblEntryOfSAO[i])->Header.DimmType & DimmType) != 0) {
      if (((EntryOfTables->TblEntryOfSAO[i])->Header.NumOfDimm & NOD) != 0) {
        if (!NBPtr->IsSupported[SelectMotherboardLayer] || ((EntryOfTables->TblEntryOfSAO[i])->Header.MotherboardLayer & MotherboardLayer) != 0) {
          if (!NBPtr->IsSupported[SelectMotherboardPower] || ((EntryOfTables->TblEntryOfSAO[i])->Header.MotherboardPower & MotherboardPower) != 0) {
            if (!NBPtr->IsSupported[DqsRoutingTypeDependence] || ((EntryOfTables->TblEntryOfSAO[i])->Header.DqsRoutingType & NBPtr->DqsRoutingType) != 0) {
              //
              // Determine if this is the expected NB Type
              //
              LogicalCpuid = (EntryOfTables->TblEntryOfSAO[i])->Header.LogicalCpuid;
              PackageType = (EntryOfTables->TblEntryOfSAO[i])->Header.PackageType;
              if (MemPIsIdSupported (NBPtr, LogicalCpuid, PackageType)) {
                TblPtr = (PSCFG_SAO_ENTRY *) ((EntryOfTables->TblEntryOfSAO[i])->TBLPtr);
                TableSize = (EntryOfTables->TblEntryOfSAO[i])->TableSize;
                break;
              }
            }
          }
        }
      }
    }
    i++;
  }

  // Check whether no table entry is found.
  if (EntryOfTables->TblEntryOfSAO[i] == NULL) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\nNo SlowAccMode, AddrTmg and ODCCtrl  table\n");
    return FALSE;
  }

  CurDDRrate = (UINT32) (1 << (CurrentChannel->DCTPtr->Timings.Speed / 66));
  DDRVoltage = (UINT8) (1 << CONVERT_VDDIO_TO_ENCODED (NBPtr->RefPtr->DDRVoltage, CurrentChannel->TechType));
  RankTypeOfPopulatedDimm = MemPGetPsRankType (CurrentChannel);

  for (i = 0; i < TableSize; i++) {
    MemPConstructRankTypeMap ((UINT16) TblPtr->Dimm0, (UINT16) TblPtr->Dimm1, (UINT16) TblPtr->Dimm2, &RankTypeInTable);
    if ((TblPtr->DimmPerCh & NOD) != 0) {
      if ((TblPtr->DDRrate & CurDDRrate) != 0) {
        if ((TblPtr->VDDIO & DDRVoltage) != 0) {
          if ((RankTypeInTable & RankTypeOfPopulatedDimm) == RankTypeOfPopulatedDimm) {
            CurrentChannel->DctAddrTmg = TblPtr->AddTmgCtl;
            IDS_OPTION_HOOK (IDS_MEM_ADDR_CMD_TMG, &CurrentChannel->DctAddrTmg, &(NBPtr->MemPtr->StdHeader));
            CurrentChannel->DctOdcCtl = TblPtr->ODC;
            CurrentChannel->SlowMode = (TblPtr->SlowMode == 1) ? TRUE : FALSE;
            NBPtr->PsPtr->ProcessorOnDieTerminationOff = (TblPtr->POdtOff == 1) ? TRUE : FALSE;
            break;
          }
        }
      }
    }
    TblPtr++;
  }

  //
  // If there is no entry, check if overriding values (SlowAccMode, AddrTmg and ODCCtrl) existed. If not, show no entry found.
  //
  PsoMaskSAO = (UINT8) MemPProceedTblDrvOverride (NBPtr, NBPtr->RefPtr->PlatformMemoryConfiguration, PSO_TBLDRV_SLOWACCMODE);
  PsoMaskSAO &= (UINT8) MemPProceedTblDrvOverride (NBPtr, NBPtr->RefPtr->PlatformMemoryConfiguration, PSO_TBLDRV_ODCCTRL);
  PsoMaskSAO &= (UINT8) MemPProceedTblDrvOverride (NBPtr, NBPtr->RefPtr->PlatformMemoryConfiguration, PSO_TBLDRV_ADDRTMG);
  if ((PsoMaskSAO == 0) && (i == TableSize)) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\nNo SlowAccMode, AddrTmg and ODCCtrl entries\n");
  } else {
    return TRUE;
  }

  if (NBPtr->SharedPtr->VoltageMap != VDDIO_DETERMINED) {
    return TRUE;
  }

  PutEventLog (AGESA_ERROR, MEM_ERROR_SAO_NOT_FOUND, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
  SetMemError (AGESA_ERROR, NBPtr->MCTPtr);
  if (!NBPtr->MemPtr->ErrorHandling (NBPtr->MCTPtr, NBPtr->Dct, EXCLUDE_ALL_CHIPSEL, &NBPtr->MemPtr->StdHeader)) {
    ASSERT (FALSE);
  }
  return FALSE;
}

