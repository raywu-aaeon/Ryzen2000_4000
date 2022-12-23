/* $NoKeywords:$ */
/**
 * @file
 *
 * mnreg.c
 *
 * Common Northbridge register access functions
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/)
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


#include <Library/BaseLib.h>
#include "AGESA.h"
#include "Library/AmdBaseLib.h"
#include "Library/AmdMemBaseV5Lib.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mm.h"
#include "mn.h"
#include "merrhdl.h"
#include "Library/AmdHeapLib.h"
#include "Filecode.h"
CODE_GROUP (G1_PEICC)
RDATA_GROUP (G1_PEICC)

#define FILECODE LIBRARY_MEM_NBLIB_MNREG_FILECODE


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
MemNErrorRecoveryStatus (
  IN OUT   BOOLEAN Status
  );

VOID
MemNIgnoreErrorStatus (
  IN OUT   BOOLEAN Status
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
 *   This function sets the current DCT to work on.
 *   Should be called before accessing a certain DCT
 *   All data structures will be updated to point to the current DCT
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   Dct - ID of the target DCT
 *
 */

VOID
MemNSwitchDCTNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 Dct
  )
{
  ASSERT (NBPtr->DctCount > Dct);
  //
  // Set the DctCfgSel to new DCT
  //
  NBPtr->FamilySpecificHook[DCTSelectSwitch] (NBPtr, &Dct);
  NBPtr->Dct = Dct;
  NBPtr->MCTPtr->Dct = NBPtr->Dct;
  NBPtr->DCTPtr = &(NBPtr->MCTPtr->DctData[NBPtr->Dct]);
  NBPtr->PsPtr = &(NBPtr->PSBlock[NBPtr->Dct]);
  NBPtr->DctCachePtr = &(NBPtr->DctCache[NBPtr->Dct]);

  MemNSwitchChannelNb (NBPtr, NBPtr->Channel);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function is used by families that use a separate DctCfgSel bit to
 *     select the current DCT which will be accessed by function 2.
 *     NOTE:  This function must be called BEFORE the NBPtr->Dct variable is
 *     updated.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       *Dct     - Pointer to ID of the target DCT
 *
 */

BOOLEAN
MemNDctCfgSelectUnb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       VOID *Dct
  )
{
  //
  // Sanity check the current DctCfgSel setting
  //
  ASSERT (NBPtr->Dct == NBPtr->GetBitField (NBPtr, BFDctCfgSel));
  //
  // Set the DctCfgSel to new DCT
  //
  NBPtr->SetBitField (NBPtr, BFDctCfgSel, *(UINT8*)Dct);

  return TRUE;
}


/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function sets the current channel to work on.
 *   Should be called before accessing a certain channel
 *   All data structures will be updated to point to the current channel
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   Channel - ID of the target channel
 *
 */

VOID
MemNSwitchChannelNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 Channel
  )
{
  NBPtr->Channel = Channel ? 1 : 0;
  NBPtr->ChannelPtr = &(NBPtr->DCTPtr->ChData[NBPtr->Channel]);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function gets a bit field from PCI register
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   FieldName - Field name
 *
 *     @return      Bit field value
 */

UINT32
MemNGetBitFieldNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINTN FieldName
  )
{
  UINT32 Value;

  Value = NBPtr->MemNCmnGetSetFieldNb (NBPtr, 0, FieldName, 0);
  return Value;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *   This function sets a bit field from PCI register
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   FieldName - Field name
 *     @param[in]   Field - Value to be stored in PCT register
 *
 */

VOID
MemNSetBitFieldNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINTN FieldName,
  IN       UINT32 Field
  )
{
  NBPtr->MemNCmnGetSetFieldNb (NBPtr, 1, FieldName, Field);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Check if bitfields of all enabled DCTs on a die have the expected value. Ignore
 *  DCTs that are disabled.
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   FieldName - Bit Field name
 *     @param[in]   Field - Value to be checked
 *
 *     @return          TRUE -  All enabled DCTs have the expected value on the bitfield.
 *     @return          FALSE - Not all enabled DCTs have the expected value on the bitfield.
 *
 * ----------------------------------------------------------------------------
 */
BOOLEAN
MemNBrdcstCheckNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINTN FieldName,
  IN       UINT32 Field
  )
{
  UINT8 Dct;
  UINT8 CurrentDCT;
  Dct = NBPtr->Dct;
  for (CurrentDCT = 0; CurrentDCT < NBPtr->DctCount; CurrentDCT++) {
    MemNSwitchDCTNb (NBPtr, CurrentDCT);
    if ((NBPtr->DCTPtr->Timings.DctMemSize != 0) && !((CurrentDCT == 1) && NBPtr->Ganged)) {
      if (MemNGetBitFieldNb (NBPtr, FieldName) != Field) {
        MemNSwitchDCTNb (NBPtr, Dct);
        return FALSE;
      }
    }
  }
  MemNSwitchDCTNb (NBPtr, Dct);
  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Set bitfields of all enabled DCTs on a die to a value. Ignore
 *  DCTs that are disabled.
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   FieldName - Bit Field name
 *     @param[in]   Field - Value to be set
 *
 * ----------------------------------------------------------------------------
 */
VOID
MemNBrdcstSetNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINTN FieldName,
  IN       UINT32 Field
  )
{
  UINT8 Dct;
  UINT8 CurrentDCT;
  Dct = NBPtr->Dct;
  for (CurrentDCT = 0; CurrentDCT < NBPtr->DctCount; CurrentDCT++) {
    MemNSwitchDCTNb (NBPtr, CurrentDCT);
    if ((NBPtr->DCTPtr->Timings.DctMemSize != 0) && !((CurrentDCT == 1) && NBPtr->Ganged)) {
      MemNSetBitFieldNb (NBPtr, FieldName, Field);
    }
  }
  MemNSwitchDCTNb (NBPtr, Dct);
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *  Set bitfields of all DCTs regardless of if they are being enabled or not on a
 *  die to a value.
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   FieldName - Bit Field name
 *     @param[in]   Field - Value to be set
 *
 * ----------------------------------------------------------------------------
 */
VOID
MemNBrdcstSetUnConditionalNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINTN FieldName,
  IN       UINT32 Field
  )
{
  UINT8 Dct;
  UINT8 CurrentDCT;
  Dct = NBPtr->Dct;
  for (CurrentDCT = 0; CurrentDCT < NBPtr->DctCount; CurrentDCT++) {
    MemNSwitchDCTNb (NBPtr, CurrentDCT);
    MemNSetBitFieldNb (NBPtr, FieldName, Field);
  }
  MemNSwitchDCTNb (NBPtr, Dct);
}

/*-----------------------------------------------------------------------------*/
/**
 *      This function calculates the memory channel index relative to the
 *      socket, taking the Die number, the Dct, and the channel.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in] Dct
 *     @param[in] Channel
 *
 */
UINT8
MemNGetSocketRelativeChannelNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINT8 Dct,
  IN       UINT8 Channel
  )
{
  return ((NBPtr->MCTPtr->DieId * NBPtr->DctCount) + Dct);
}
/*-----------------------------------------------------------------------------*/
/**
 *      This function records the error recovery status
 *
 *     @param[in,out]   Status   - Error recovery status
 */
VOID
MemNErrorRecoveryStatus (
  IN OUT   BOOLEAN Status
  )
{
}
/*-----------------------------------------------------------------------------*/
/**
 *      This function ignores the error recovery status
 *
 *     @param[in,out]   Status   - Error recovery status
 */
VOID
MemNIgnoreErrorStatus (
  IN OUT   BOOLEAN Status
  )
{
}
/* -----------------------------------------------------------------------------*/
/**
 *
 *  Poll a bitfield. If the bitfield does not get set to the target value within
 *  specified microseconds, it times out.
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]   FieldName - Bit Field name
 *     @param[in]   Field - Value to be set
 *     @param[in]   MicroSecond - Number of microsecond to wait
 *     @param[in]   IfBroadCast - Need to broadcast to both DCT or not
 *
 * ----------------------------------------------------------------------------
 */
VOID
MemNPollBitFieldNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       UINTN FieldName,
  IN       UINT32 Field,
  IN       UINT32 MicroSecond,
  IN       BOOLEAN IfBroadCast
  )
{
  BOOLEAN ErrorRecovery;
  BOOLEAN IgnoreErr;
  UINT8 ExcludeDCT;
  UINT16 ExcludeChipSelMask;
  UINT32 EventInfo;
  UINT64 InitTSC;
  UINT64 CurrentTSC;
  UINT64 TimeOut;
  AGESA_STATUS EventClass;
  MEM_DATA_STRUCT *MemPtr;
  DIE_STRUCT *MCTPtr;
  BOOLEAN TimeoutEn;

  MemPtr = NBPtr->MemPtr;
  MCTPtr = NBPtr->MCTPtr;
  ExcludeDCT = EXCLUDE_ALL_DCT;
  ExcludeChipSelMask = EXCLUDE_ALL_CHIPSEL;
  TimeoutEn = TRUE;
  IDS_TIMEOUT_CTL (&TimeoutEn);

  CurrentTSC = 0;
  InitTSC = AsmReadMsr64 (TSC);
  TimeOut = InitTSC + ((UINT64) MicroSecond * MemPtr->TscRate);

  while ((CurrentTSC < TimeOut) || !TimeoutEn) {
    if (IfBroadCast) {
      if (NBPtr->BrdcstCheck (NBPtr, FieldName, Field)) {
        break;
      }
    } else {
      if (MemNGetBitFieldNb (NBPtr, FieldName) == Field) {
        break;
      }
    }
    CurrentTSC = AsmReadMsr64 (TSC);
  }

  if ((CurrentTSC >= TimeOut) && TimeoutEn) {
    ErrorRecovery = TRUE;
    IgnoreErr = FALSE;
    MemNErrorRecoveryStatus (ErrorRecovery);
    MemNIgnoreErrorStatus (IgnoreErr);
    IDS_OPTION_HOOK (IDS_MEM_ERROR_RECOVERY, &ErrorRecovery, &MemPtr->StdHeader);
    IDS_OPTION_HOOK (IDS_MEM_IGNORE_ERROR, &IgnoreErr, &MemPtr->StdHeader);

    // Default event class
    // If different event class is needed in one entry, override it.
    EventClass = AGESA_ERROR;
    switch (FieldName) {
    case BFDramEnabled:
      EventInfo = MEM_ERROR_DRAM_ENABLED_TIME_OUT;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tDramEnabled bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFDctAccessDone:
      EventInfo = MEM_ERROR_DCT_ACCESS_DONE_TIME_OUT;
      ExcludeDCT = NBPtr->Dct;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tDctAccessDone bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFSendCtrlWord:
      EventInfo = MEM_ERROR_SEND_CTRL_WORD_TIME_OUT;
      ExcludeDCT = NBPtr->Dct;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tSendCtrlWord bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFPrefDramTrainMode:
      EventInfo = MEM_ERROR_PREF_DRAM_TRAIN_MODE_TIME_OUT;
      ExcludeDCT = NBPtr->Dct;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tPrefDramTrainMode bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFEnterSelfRef:
      EventInfo = MEM_ERROR_ENTER_SELF_REF_TIME_OUT;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tEnterSelfRef bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFFreqChgInProg:
      EventInfo = MEM_ERROR_FREQ_CHG_IN_PROG_TIME_OUT;
      ExcludeDCT = NBPtr->Dct;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tFreqChgInProg bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFExitSelfRef:
      EventInfo = MEM_ERROR_EXIT_SELF_REF_TIME_OUT;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tExitSelfRef bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFSendMrsCmd:
      EventInfo = MEM_ERROR_SEND_MRS_CMD_TIME_OUT;
      ExcludeDCT = NBPtr->Dct;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tSendMrsCmd bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFSendZQCmd:
      EventInfo = MEM_ERROR_SEND_ZQ_CMD_TIME_OUT;
      ExcludeDCT = NBPtr->Dct;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tSendZQCmd bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFDctExtraAccessDone:
      EventInfo = MEM_ERROR_DCT_EXTRA_ACCESS_DONE_TIME_OUT;
      ExcludeDCT = NBPtr->Dct;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tDctExtraAccessDone bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFMemClrBusy:
      EventInfo = MEM_ERROR_MEM_CLR_BUSY_TIME_OUT;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tMemClrBusy bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFMemCleared:
      EventInfo = MEM_ERROR_MEM_CLEARED_TIME_OUT;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tMemCleared bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFFlushWr:
      EventInfo = MEM_ERROR_FLUSH_WR_TIME_OUT;
      ExcludeDCT = NBPtr->Dct;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tFlushWr bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFCurNbPstate:
      EventInfo = MEM_ERROR_NBPSTATE_TRANSITION_TIME_OUT;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tCurNBPstate bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFCurNbPstateLo:
      EventInfo = MEM_ERROR_NBPSTATE_TRANSITION_TIME_OUT;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tCurNBPstateLo bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFNbPstateReqBusy:
      EventInfo = MEM_ERROR_NBPSTATE_TRANSITION_TIME_OUT;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tNbPstateReqBusy bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFCurNbVid:
      EventInfo = MEM_ERROR_NBPSTATE_TRANSITION_TIME_OUT;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tCurNbVid bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFCurNbDid:
      EventInfo = MEM_ERROR_NBPSTATE_TRANSITION_TIME_OUT;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tCurNbDid bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    case BFCurNbFid:
      EventInfo = MEM_ERROR_NBPSTATE_TRANSITION_TIME_OUT;
      IDS_HDT_CONSOLE (MEM_FLOW, "\tCurNbFid bitfield times out.\n");
      ASSERT (ErrorRecovery || IgnoreErr);
      break;
    default:
      EventClass = AGESA_SUCCESS;
      EventInfo = 0;
      IDS_ERROR_TRAP;
    }

    PutEventLog (EventClass, EventInfo, NBPtr->Node, NBPtr->Dct, NBPtr->Channel, 0, &MemPtr->StdHeader);
    SetMemError (EventClass, MCTPtr);
    if (!MemPtr->ErrorHandling (MCTPtr, ExcludeDCT, ExcludeChipSelMask, &MemPtr->StdHeader)) {
      ASSERT (FALSE);
    }
  }
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *
 *     This function changes memory Pstate context
 *
 *     @param[in,out]  *NBPtr     - Pointer to the MEM_NB_BLOCK
 *     @param[in]      MemPstate  - Target Memory Pstate
 *
 *     @return    TRUE
 * ----------------------------------------------------------------------------
 */
VOID
MemNChangeMemPStateContextNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       MEM_PSTATE MemPstate
  )
{
  ASSERT ((MemPstate == 0) || (MemPstate == 1));

  IDS_HDT_CONSOLE (MEM_SETREG, "\nGo to Memory Pstate Conext %d\n", MemPstate);

  NBPtr->MemPstate = (MemPstate == 0) ? MEMORY_PSTATE0 : MEMORY_PSTATE1;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *   This function allocates buffer for NB register table
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *     @param[in]       Handle   - Handle for heap allocation for NBRegTable
 *
 *     @return      TRUE  - Successfully allocates buffer the first time
 *     @return      FALSE - Buffer already allocated or fails to allocate
 */

BOOLEAN
MemNAllocateNBRegTableNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN       NB_REG_TAB_HANDLE  Handle
  )
{
  ALLOCATE_HEAP_PARAMS AllocHeapParams;
  LOCATE_HEAP_PTR LocHeap;

  // If NBRegTable for this family exists, use it
  LocHeap.BufferHandle = GENERATE_MEM_HANDLE (ALLOC_NB_REG_TABLE, Handle, 0, 0);
  if (HeapLocateBuffer (&LocHeap, &(NBPtr->MemPtr->StdHeader)) == AGESA_SUCCESS) {
    NBPtr->NBRegTable = (TSEFO *) LocHeap.BufferPtr;
    return FALSE;
  }

  // Allocate new buffer for NBRegTable if it has not been allocated
  AllocHeapParams.RequestedBufferSize = sizeof (TSEFO) * BFEndOfList;
  AllocHeapParams.BufferHandle = GENERATE_MEM_HANDLE (ALLOC_NB_REG_TABLE, Handle, 0, 0);
  AllocHeapParams.Persist = HEAP_SYSTEM_MEM;
  if (AGESA_SUCCESS != HeapAllocateBuffer (&AllocHeapParams, &(NBPtr->MemPtr->StdHeader))) {
    ASSERT(FALSE); // NB and Tech Block Heap allocate error
    return FALSE;
  }
  NBPtr->NBRegTable = (TSEFO *)AllocHeapParams.BufferPtr;
  return TRUE;
}

/*-----------------------------------------------------------------------------
 *
 *
 *     This function is an empty function used to intialize FamilySpecificHook array
 *
 *     @param[in,out]  *NBPtr     - Pointer to the MEM_NB_BLOCK
 *     @param[in,out]  OptParam   - Optional parameter
 *
 *     @return  TRUE - always
 * ----------------------------------------------------------------------------
 */
BOOLEAN
MemNDefaultFamilyHookNb (
  IN OUT   MEM_NB_BLOCK *NBPtr,
  IN OUT   VOID *OptParam
  )
{
  return TRUE;
}

