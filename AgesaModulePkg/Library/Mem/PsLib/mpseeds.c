/* $NoKeywords:$ */
/**
 * @file
 *
 * mpseeds.c
 *
 * A sub-engine extracts WL and HW RxEn seeds from PSCFG tables.
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/Ps)
 * @e \$Revision: 309090 $ @e \$Date: 2014-12-10 02:28:05 +0800 (Wed, 10 Dec 2014) $
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

#define FILECODE LIBRARY_MEM_PSLIB_MPSEEDS_FILECODE


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
MemPGetTrainingSeeds (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  );
/* -----------------------------------------------------------------------------*/
/**
 *
 *    A sub-function extracts WL and HW RxEn seeds from PSCFG tables
 *    from a input table
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *EntryOfTables     - Pointer to MEM_PSC_TABLE_BLOCK
 *
 *     @return          NBPtr->PsPtr->WLSeedVal
 *     @return          NBPtr->PsPtr->HWRxENSeedVal
 *
 */
BOOLEAN
MemPGetTrainingSeeds (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  )
{

  UINT8 i;
  UINT8 MaxDimmPerCh;
  UINT8 MaxDimmSlotPerCh;
  UINT8 NOD;
  UINT8 TableSize;
  DIMM_TYPE DimmType;
  SOC_LOGICAL_ID LogicalCpuid;
  UINT8 PackageType;
  UINT8 Seedloop;
  UINT8 CH;
  PSC_TBL_ENTRY **TblEntryPtr;
  PSCFG_SEED_ENTRY *TblPtr;
  CH_DEF_STRUCT *CurrentChannel;

  CurrentChannel = NBPtr->ChannelPtr;
  TblEntryPtr = NULL;
  TblPtr = NULL;
  TableSize = 0;
  PackageType = 0;
  LogicalCpuid.Family = AMD_FAMILY_UNKNOWN;

  MaxDimmPerCh = GetMaxDimmsPerChannel (NBPtr->RefPtr->PlatformMemoryConfiguration, NBPtr->MCTPtr->SocketId, CurrentChannel->ChannelID);
  MaxDimmSlotPerCh = MaxDimmPerCh - GetMaxSolderedDownDimmsPerChannel (NBPtr->RefPtr->PlatformMemoryConfiguration,
                                                                       NBPtr->MCTPtr->SocketId, CurrentChannel->ChannelID);
  CH = 1 << (CurrentChannel->ChannelID);

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
  NOD = (UINT8) (MaxDimmSlotPerCh != 0) ? (1 << (MaxDimmSlotPerCh - 1)) : _DIMM_NONE;

  // Get seed value of WL, then HW RxEn
  for (Seedloop = 0; Seedloop < 2; Seedloop++) {
    TblEntryPtr = (Seedloop == 0) ? EntryOfTables->TblEntryOfWLSeed : EntryOfTables->TblEntryOfHWRxENSeed;

    i = 0;
    // Obtain table pointer, table size, Logical Cpuid and PSC type according to Dimm, NB and package type.
    while (TblEntryPtr[i] != NULL) {
      if (((TblEntryPtr[i])->Header.DimmType & DimmType) != 0) {
        //
        // Determine if this is the expected NB Type
        //
        LogicalCpuid = (TblEntryPtr[i])->Header.LogicalCpuid;
        PackageType = (TblEntryPtr[i])->Header.PackageType;
        if (MemPIsIdSupported (NBPtr, LogicalCpuid, PackageType)) {
          TblPtr = (PSCFG_SEED_ENTRY *) ((TblEntryPtr[i])->TBLPtr);
          TableSize = (TblEntryPtr[i])->TableSize;
          break;
        }
      }
      i++;
    }

    // Check whether no table entry is found.
    if (TblEntryPtr[i] == NULL) {
      IDS_HDT_CONSOLE (MEM_FLOW, "\nNo %s training seeds Config table\n", (Seedloop == 0) ? "WL" : "HW RxEn");
      return FALSE;
    }

    for (i = 0; i < TableSize; i++) {
      if ((TblPtr->DimmPerCh & NOD) != 0) {
        if ((TblPtr->Channel & CH) != 0) {
          if (Seedloop == 0) {
            NBPtr->PsPtr->WLSeedVal = (UINT8) TblPtr->SeedVal;
          } else {
            NBPtr->PsPtr->HWRxENSeedVal = TblPtr->SeedVal;
          }
          break;
        }
      }
      TblPtr++;
    }

    if (i == TableSize) {
      IDS_HDT_CONSOLE (MEM_FLOW, "\nNo %s seed entries\n\n", (Seedloop == 0) ? "WL" : "HW RxEn");
      PutEventLog (AGESA_ERROR, MEM_ERROR_TRAINING_SEED_NOT_FOUND, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
      SetMemError (AGESA_ERROR, NBPtr->MCTPtr);
      if (!NBPtr->MemPtr->ErrorHandling (NBPtr->MCTPtr, NBPtr->Dct, EXCLUDE_ALL_CHIPSEL, &NBPtr->MemPtr->StdHeader)) {
        ASSERT (FALSE);
      }
      return FALSE;
    }
  }

  return TRUE;
}
