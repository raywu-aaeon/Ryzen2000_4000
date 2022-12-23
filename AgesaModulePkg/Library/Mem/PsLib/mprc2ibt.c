/* $NoKeywords:$ */
/**
 * @file
 *
 * mprc2ibt.c
 *
 * A sub-engine which extracts RC2[IBT] value for RDIMM configuration.
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
#define FILECODE LIBRARY_MEM_PSLIB_MPRC2IBT_FILECODE


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
MemPGetRC2IBT (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  );
/* -----------------------------------------------------------------------------*/
/**
 *
 *    A sub-function which extracts RC2[IBT] value from a input table and stores extracted
 *    value to a specific address.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *EntryOfTables       Pointer to MEM_PSC_TABLE_BLOCK
 *
 *     @return          TRUE - Table values can be extracted for all present dimms/ranks
 *     @return          FALSE - Table values cannot be extracted for all present dimms/ranks
 *
 */
BOOLEAN
MemPGetRC2IBT (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  )
{
  UINT8 i;
  UINT8 MaxDimmPerCh;
  UINT8 NOD;
  UINT8 DimmIndex;
  UINT8 TableSize;
  UINT32 CurDDRrate;
  UINT8 DDRVoltage;
  UINT16 RankTypeOfPopulatedDimm;
  UINT16 RankTypeInTable;
  SOC_LOGICAL_ID LogicalCpuid;
  UINT8 PackageType;
  UINT8 TgtDimmType;
  UINT8 NumOfReg;
  UINT8 PsoDimmMaskRc2Ibt;
  UINT8 NoEntryDimmMask;
  PSCFG_MR2IBT_ENTRY *TblPtr;
  PSCFG_MR2IBT_ENTRY *OrgTblPtr;
  CH_DEF_STRUCT *CurrentChannel;

  CurrentChannel = NBPtr->ChannelPtr;

  if (CurrentChannel->RegDimmPresent == 0) {
    return TRUE;
  }

  TblPtr = NULL;
  TableSize = 0;
  PackageType = 0;
  NoEntryDimmMask = 0;
  LogicalCpuid.Family = AMD_FAMILY_UNKNOWN;
  MaxDimmPerCh = GetMaxDimmsPerChannel (NBPtr->RefPtr->PlatformMemoryConfiguration, NBPtr->MCTPtr->SocketId, CurrentChannel->ChannelID);
  NOD = (UINT8) 1 << (MaxDimmPerCh - 1);

  i = 0;
  // Obtain table pointer, table size, Logical Cpuid and PSC type according to NB type and package type.
  while (EntryOfTables->TblEntryOfRC2IBT[i] != NULL) {
    if (((EntryOfTables->TblEntryOfRC2IBT[i])->Header.NumOfDimm & NOD) != 0) {
      LogicalCpuid = (EntryOfTables->TblEntryOfRC2IBT[i])->Header.LogicalCpuid;
      PackageType = (EntryOfTables->TblEntryOfRC2IBT[i])->Header.PackageType;
      //
      // Determine if this is the expected NB Type
      //
      if (MemPIsIdSupported (NBPtr, LogicalCpuid, PackageType)) {
        TblPtr = (PSCFG_MR2IBT_ENTRY *) ((EntryOfTables->TblEntryOfRC2IBT[i])->TBLPtr);
        TableSize = (EntryOfTables->TblEntryOfRC2IBT[i])->TableSize;
        break;
      }
    }
    i++;
  }

  // Check whether no table entry is found.
  if (EntryOfTables->TblEntryOfRC2IBT[i] == NULL) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\nNo RC2 IBT table\n");
    return FALSE;
  }

  CurDDRrate = (UINT32) (1 << (CurrentChannel->DCTPtr->Timings.Speed / 66));
  DDRVoltage = (UINT8) (1 << CONVERT_VDDIO_TO_ENCODED (NBPtr->RefPtr->DDRVoltage, CurrentChannel->TechType));
  RankTypeOfPopulatedDimm = MemPGetPsRankType (CurrentChannel);

  OrgTblPtr = TblPtr;
  for (DimmIndex = 0; DimmIndex < MAX_DIMMS_PER_CHANNEL; DimmIndex++) {
    TblPtr = OrgTblPtr;
    NumOfReg = NBPtr->PsPtr->NumOfReg[DimmIndex];
    if ((CurrentChannel->ChDimmValid & (UINT8) (1 << DimmIndex)) != 0) {
      if ((CurrentChannel->DimmQrPresent & (UINT8) (1 << DimmIndex)) != 0) {
        TgtDimmType = DIMM_QR;
      } else if ((CurrentChannel->DimmDrPresent & (UINT8) (1 << DimmIndex)) != 0) {
        TgtDimmType = DIMM_DR;
      } else {
        TgtDimmType = DIMM_SR;
      }

      for (i = 0; i < TableSize; i++) {
        MemPConstructRankTypeMap ((UINT16) TblPtr->Dimm0, (UINT16) TblPtr->Dimm1, (UINT16) TblPtr->Dimm2, &RankTypeInTable);
        if ((TblPtr->DimmPerCh & NOD) != 0) {
          if ((TblPtr->DDRrate & CurDDRrate) != 0) {
            if ((TblPtr->VDDIO & DDRVoltage) != 0) {
              if ((RankTypeInTable & RankTypeOfPopulatedDimm) == RankTypeOfPopulatedDimm) {
                if ((TblPtr->Dimm & TgtDimmType) != 0) {
                  // If TblPtr->NumOfReg == 0x0F, that means the condition will be TRUE regardless of NumRegisters in DIMM
                  if ((TblPtr->NumOfReg == 0xF) || (TblPtr->NumOfReg == NumOfReg)) {
                    CurrentChannel->CtrlWrd02[DimmIndex] = (UINT8) ((TblPtr->IBT & 0x1) << 2);
                    CurrentChannel->CtrlWrd08[DimmIndex] = (UINT8) ((TblPtr->IBT & 0xE) >> 1);
                    break;
                  }
                }
              }
            }
          }
        }
        TblPtr++;
      }

      if (i == TableSize) {
        NoEntryDimmMask |= (UINT8) 1 << DimmIndex;
      }
    }
  }

  //
  // If there are no entries for certain Dimm(s), check if overriding value existed for them. If not, return FALSE.
  //
  PsoDimmMaskRc2Ibt = (UINT8) MemPProceedTblDrvOverride (NBPtr, NBPtr->RefPtr->PlatformMemoryConfiguration, PSO_TBLDRV_RC2_IBT);
  if (NoEntryDimmMask != 0) {
    if ((NoEntryDimmMask & PsoDimmMaskRc2Ibt) != NoEntryDimmMask) {
      IDS_HDT_CONSOLE (MEM_FLOW, "\nNo RC2 IBT entries\n");
      PutEventLog (AGESA_ERROR, MEM_ERROR_RC2_IBT_NOT_FOUND, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
      SetMemError (AGESA_ERROR, NBPtr->MCTPtr);
      if (!NBPtr->MemPtr->ErrorHandling (NBPtr->MCTPtr, NBPtr->Dct, EXCLUDE_ALL_CHIPSEL, &NBPtr->MemPtr->StdHeader)) {
        ASSERT (FALSE);
      }
      return FALSE;
    }
  }

  return TRUE;
}
