/* $NoKeywords:$ */
/**
 * @file
 *
 * mpdatacfgD3.c
 *
 * Sub-engine to extract DDR43 data bus settings from recommended table
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

#define FILECODE LIBRARY_MEM_PSLIB_MPDATACFGD3_FILECODE

/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define _DONT_CARE 0xFF

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

/* -----------------------------------------------------------------------------*/
/**
 *
 *     Look up data Bus config tables and return the pointer to the matched entry.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *EntryOfTables     - Pointer to MEM_PSC_TABLE_BLOCK
 *
 *     @return          TRUE - Table values can be extracted per dimm population and ranks type.
 *     @return          FALSE - Table values cannot be extracted per dimm population and ranks type.
 *
 */
BOOLEAN
MemPLookupDataBusCfgTabs3 (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSC_TABLE_BLOCK *EntryOfTables
  )
{
  UINT8   i;
  UINT8   TableSize;
  UINT32  CurDDRrate;
  UINT8   DDRVoltage;
  UINT16  RankTypeInTable;
  UINT8   PsoMaskSAO;
  UINT8   Chipsel;
  PSCFG_DATABUS_ENTRY_D3 *TblPtr;
  CH_DEF_STRUCT *CurrentChannel;

  CurrentChannel = NBPtr->ChannelPtr;

  if (CurrentChannel->TechType != DDR3_TECHNOLOGY) {
    return FALSE;
  }

  TblPtr = (PSCFG_DATABUS_ENTRY_D3 *) MemPGetTableEntry (NBPtr, EntryOfTables->TblEntryOfDramTerm, &TableSize);
  IDS_HDT_CONSOLE(MEM_FLOW,"\t\tLooking up data bus config entries\n");

  if (TblPtr != NULL) {
    CurDDRrate = (UINT32) (1 << (CurrentChannel->DCTPtr->Timings.Speed / 66));
    DDRVoltage = (UINT8) (1 << CONVERT_VDDIO_TO_ENCODED (NBPtr->RefPtr->DDRVoltage, CurrentChannel->TechType));
    IDS_HDT_CONSOLE(MEM_FLOW,"\t\t\t            NumDimmSlots   DDR Rate     VDDIO      Rank Type\n");
    IDS_HDT_CONSOLE(MEM_FLOW,"\t\t\t Current ->      %d         %08x       %02x         %x\n",
                    NBPtr->PsPtr->NumOfDimmSlots, CurDDRrate, DDRVoltage, NBPtr->PsPtr->RankType);
    for (i = 0; i < TableSize; i++) {
      RankTypeInTable = ((UINT16) TblPtr->Dimm0) | ((UINT16) TblPtr->Dimm1 << 4) | (NP << 8) | (NP << 12);
      IDS_HDT_CONSOLE(MEM_FLOW,"\t\t\t    %d            %d         %08x       %02x         %04x\n",
                      i, TblPtr->DimmPerCh, TblPtr->DDRrate, TblPtr->VDDIO, RankTypeInTable);
      if ((TblPtr->DimmPerCh & NBPtr->PsPtr->NumOfDimmSlots) != 0) {
        if ((TblPtr->DDRrate & CurDDRrate) != 0) {
          if ((TblPtr->VDDIO & DDRVoltage) != 0) {
            if ((RankTypeInTable & NBPtr->PsPtr->RankType) == NBPtr->PsPtr->RankType) {
              for (Chipsel = 0; Chipsel < MAX_CS_PER_CHANNEL; Chipsel++) {
                NBPtr->PsPtr->RttNom[Chipsel] = (UINT8) TblPtr->RttNom;
                NBPtr->PsPtr->RttWr[Chipsel] = (UINT8) TblPtr->RttWr;
              }
              NBPtr->PsPtr->DqStrength  = (UINT8) TblPtr->DqStrength;
              NBPtr->PsPtr->DqsStrength = (UINT8) TblPtr->DqsStrength;
              NBPtr->PsPtr->OdtStrength = (UINT8) TblPtr->OdtStrength;
              break;
            }
          }
        }
      }
      TblPtr++;
    }
  } else {
    i = TableSize = 0;
  }

  PsoMaskSAO = (UINT8) MemPProceedTblDrvOverride (NBPtr, NBPtr->RefPtr->PlatformMemoryConfiguration, PSO_TBLDRV_SLOWACCMODE);
  PsoMaskSAO &= (UINT8) MemPProceedTblDrvOverride (NBPtr, NBPtr->RefPtr->PlatformMemoryConfiguration, PSO_TBLDRV_ADDRTMG);
  if ((PsoMaskSAO == 0) && (i == TableSize)) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tNo data bus config entries\n");
  } else {
    IDS_HDT_CONSOLE (MEM_FLOW, "\n\t\t\tData bus config entry found:\n");
    IDS_HDT_CONSOLE (MEM_FLOW, "\n\t\t\t\tRttnom: %x Rttwr: %x DQStr: %x DQSStr %x ODTStr: %x\n\n",
                     TblPtr->RttNom, TblPtr->RttWr, NBPtr->PsPtr->DqStrength, NBPtr->PsPtr->DqsStrength, NBPtr->PsPtr->OdtStrength);
    return TRUE;
  }

  if (NBPtr->SharedPtr->VoltageMap != VDDIO_DETERMINED) {
    return TRUE;
  }
  PutEventLog (AGESA_ERROR, MEM_ERROR_DATA_BUS_CFG_NOT_FOUND, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &NBPtr->MemPtr->StdHeader);
  SetMemError (AGESA_ERROR, NBPtr->MCTPtr);
  if (!NBPtr->MemPtr->ErrorHandling (NBPtr->MCTPtr, NBPtr->Dct, EXCLUDE_ALL_CHIPSEL, &NBPtr->MemPtr->StdHeader)) {
    ASSERT (FALSE);
  }
  return FALSE;
}


