/* $NoKeywords:$ */
/**
 * @file
 *
 * mplribt.c
 *
 * A sub-engine which extracts F0RC8, F1RC0, F1RC1 and F1RC2 value for LRDIMM configuration.
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
#define FILECODE LIBRARY_MEM_PSLIB_MPLRIBT_FILECODE


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
MemPGetLRIBT (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  );
/* -----------------------------------------------------------------------------*/
/**
 *
 *    A sub-function which extracts LRDIMM F0RC8, F1RC0, F1RC1 and F1RC2 value from a input
 *    table and stores extracted value to a specific address.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *EntryOfTables     - Pointer to MEM_PSC_TABLE_BLOCK
 *
 *     @return          TRUE - Succeed in extracting the table value
 *     @return          FALSE - Fail to extract the table value
 *
 */
BOOLEAN
MemPGetLRIBT (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  )
{
  UINT8 i;
  UINT8 MaxDimmPerCh;
  UINT8 NOD;
  UINT8 TableSize;
  UINT32 CurDDRrate;
  UINT8 DDRVoltage;
  UINT16 RankTypeOfPopulatedDimm;
  UINT16 RankTypeInTable;
  UINT8 PsoMaskLRIBT;
  SOC_LOGICAL_ID LogicalCpuid;
  UINT8 PackageType;
  PSCFG_L_IBT_ENTRY *TblPtr;
  CH_DEF_STRUCT *CurrentChannel;

  CurrentChannel = NBPtr->ChannelPtr;

  if (CurrentChannel->LrDimmPresent == 0) {
    return TRUE;
  }

  TblPtr = NULL;
  TableSize = 0;
  PackageType = 0;
  LogicalCpuid.Family = AMD_FAMILY_UNKNOWN;
  MaxDimmPerCh = GetMaxDimmsPerChannel (NBPtr->RefPtr->PlatformMemoryConfiguration, NBPtr->MCTPtr->SocketId, CurrentChannel->ChannelID);
  NOD = (UINT8) 1 << (MaxDimmPerCh - 1);

  i = 0;
  // Obtain table pointer, table size, Logical Cpuid and PSC type according to NB type and package type.
  while (EntryOfTables->TblEntryOfLRIBT[i] != NULL) {
    if (((EntryOfTables->TblEntryOfLRIBT[i])->Header.NumOfDimm & NOD) != 0) {
      LogicalCpuid = (EntryOfTables->TblEntryOfLRIBT[i])->Header.LogicalCpuid;
      PackageType = (EntryOfTables->TblEntryOfLRIBT[i])->Header.PackageType;
      //
      // Determine if this is the expected NB Type
      //
      if (MemPIsIdSupported (NBPtr, LogicalCpuid, PackageType)) {
        TblPtr = (PSCFG_L_IBT_ENTRY *) ((EntryOfTables->TblEntryOfLRIBT[i])->TBLPtr);
        TableSize = (EntryOfTables->TblEntryOfLRIBT[i])->TableSize;
        break;
      }
    }
    i++;
  }

  // Check whether no table entry is found.
  if (EntryOfTables->TblEntryOfLRIBT[i] == NULL) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\nNo LRDIMM IBT table\n");
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
            NBPtr->PsPtr->F0RC8 = (UINT8) TblPtr->F0RC8;
            NBPtr->PsPtr->F1RC0 = (UINT8) TblPtr->F1RC0;
            NBPtr->PsPtr->F1RC1 = (UINT8) TblPtr->F1RC1;
            NBPtr->PsPtr->F1RC2 = (UINT8) TblPtr->F1RC2;
            break;
          }
        }
      }
    }
    TblPtr++;
  }
  //
  // If there is no entry, check if overriding value existed. If not, return FALSE
  //
  PsoMaskLRIBT = (UINT8) MemPProceedTblDrvOverride (NBPtr, NBPtr->RefPtr->PlatformMemoryConfiguration, PSO_TBLDRV_LRDIMM_IBT);
  if ((PsoMaskLRIBT == 0) && (i == TableSize)) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\nNo LRDIMM IBT entries\n");
    PutEventLog (AGESA_ERROR, MEM_ERROR_LR_IBT_NOT_FOUND, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
    SetMemError (AGESA_ERROR, NBPtr->MCTPtr);
    if (!NBPtr->MemPtr->ErrorHandling (NBPtr->MCTPtr, NBPtr->Dct, EXCLUDE_ALL_CHIPSEL, &NBPtr->MemPtr->StdHeader)) {
      ASSERT (FALSE);
    }
    return FALSE;
  }

  return TRUE;
}

