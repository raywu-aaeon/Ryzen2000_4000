/* $NoKeywords:$ */
/**
 * @file
 *
 * mnPmuSramMsgBlockCZ.c
 *
 * Common Northbridge  functions for CZ
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
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
#include "Library/IdsLib.h"
#include "Ids.h"
#include "mm.h"
#include "mn.h"
#include "mt.h"
#include "mnreg.h"
#include "mnpmu.h"
#include "merrhdl.h"
#include "mport.h"
#include "mnPmuSramMsgBlockCZ.h"
#include "Library/AmdHeapLib.h"
#include "Filecode.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)

#define FILECODE LIBRARY_MEM_NBCZLIB_MNPMUSRAMMSGBLOCKCZ_FILECODE
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
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Load the PMU SRAM Message Block to DMEM.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return  TRUE - Load the PMU SRAM Message Block successfully.
 *     @return  FALSE - Fail to load the PMU SRAM Message Block.
 */

BOOLEAN
MemNWritePmuSramMsgBlockCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT16 i;
  UINT16 *ImagePtr;
  ImagePtr = (UINT16 *) NBPtr->PsPtr->PmuSramMsgBlockPtr;

  // Only load to current DCT
  MemNSetBitFieldNb (NBPtr, BFDctCfgBcEn, 0);

  MemNSetBitFieldNb (NBPtr, BFPmuReset, 0);

  // Write the word to D18F2x[B,0]9C_x0005_[27FF:0800]_dct[3:0] (using the broadcast port for all phys at
  // D18F2xB98_dct[MaxDctMstr:0], and using the autoincrement feature).
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\tStart writing PMU SRAM Message Block...\n");
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\t Offset   Value\n");

  MemNSetBitFieldNb (NBPtr, RegDctAddlOffset, PMU_FIRMWARE_SRAM_START | DCT_ACCESS_WRITE | DCT_OFFSET_AUTO_INC_EN);

  for (i = 0; i < sizeof (PMU_SRAM_MSG_BLOCK_CZ) / sizeof (ImagePtr[0]); i++) {
    MemNSetBitFieldNb (NBPtr, RegDctAddlData, ImagePtr[i]);
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\t   %02x     %04x\n", 2 * i, ImagePtr[i]);
  }
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\tEnd writing PMU SRAM Message Block\n");
  MemNSetBitFieldNb (NBPtr, RegDctAddlOffset, 0);
  MemNSetBitFieldNb (NBPtr, BFDctCfgBcEn, 0);

  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Read the PMU SRAM Message Block from DMEM.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return  TRUE - Read the PMU SRAM Message Block successfully.
 *     @return  FALSE - Failed to read the PMU SRAM Message Block.
 */

BOOLEAN
MemNReadPmuSramMsgBlockCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT16 i;
  UINT16 *ImagePtr;
  UINT32 Address;

  ImagePtr = (UINT16 *) NBPtr->PsPtr->PmuSramMsgBlockPtr;

  // Only read current DCT
  MemNSetBitFieldNb (NBPtr, BFDctCfgBcEn, 0);

  MemNSetBitFieldNb (NBPtr, BFPmuReset, 0);

  // Write the word to D18F2x[B,0]9C_x0005_[27FF:0800]_dct[3:0] (using the broadcast port for all phys at
  // D18F2xB98_dct[MaxDctMstr:0], and using the autoincrement feature).
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\tStart reading PMU SRAM Message Block...\n");
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\t Offset   Value\n");

  Address = PMU_FIRMWARE_SRAM_START;

  for (i = 0; i < sizeof (PMU_SRAM_MSG_BLOCK_CZ) / sizeof (ImagePtr[0]); i++) {
    MemNSetBitFieldNb (NBPtr, RegDctAddlOffset, Address);
    ImagePtr[i] = (UINT16) (0xFFFF & MemNGetBitFieldNb (NBPtr, RegDctAddlData));
    Address++;
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\t   %02x     %04x\n", 2 * i, ImagePtr[i]);
  }
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\tEnd reading PMU SRAM Message Block\n");
  MemNSetBitFieldNb (NBPtr, RegDctAddlOffset, 0);
  MemNSetBitFieldNb (NBPtr, BFDctCfgBcEn, 0);

  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Initialize the PMU SRAM Message Block buffer.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return  TRUE - initialize the PMU SRAM Message buffer successfully.
 *     @return  FALSE - Fail to initialize the PMU SRAM Message buffer.
 */

BOOLEAN
MemNInitPmuSramMsgBlockCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  LOCATE_HEAP_PTR LocHeap;
  ALLOCATE_HEAP_PARAMS AllocHeapParams;
  PMU_SRAM_MSG_BLOCK_CZ *PmuSramMsgBlockPtr;
  UINT8 Dct;

  LocHeap.BufferHandle = AMD_MEM_PMU_SRAM_MSG_BLOCK_HANDLE;
  //
  // Allocate buffer for PMU SRAM Message Blocks on each channel
  //
  AllocHeapParams.RequestedBufferSize = sizeof (PMU_SRAM_MSG_BLOCK_CZ) * NBPtr->DctCount;
  AllocHeapParams.BufferHandle = AMD_MEM_PMU_SRAM_MSG_BLOCK_HANDLE;
  AllocHeapParams.Persist = HEAP_LOCAL_CACHE;

  if (HeapAllocateBuffer (&AllocHeapParams, &(NBPtr->MemPtr->StdHeader)) != AGESA_SUCCESS) {
    // Could not allocate heap for PMU SRAM Message Block.
    return FALSE;
  }
  PmuSramMsgBlockPtr = (PMU_SRAM_MSG_BLOCK_CZ *) AllocHeapParams.BufferPtr;

  LibAmdMemFill ((VOID *)PmuSramMsgBlockPtr, 0, (UINTN) (sizeof (PMU_SRAM_MSG_BLOCK_CZ) * NBPtr->DctCount) , &(NBPtr->MemPtr->StdHeader));
  //
  // Store Pointers in PS Blocks
  //
  for (Dct = 0; Dct < NBPtr->DctCount; Dct++) {
    MemNSwitchDCTNb  (NBPtr, Dct);
    IDS_HDT_CONSOLE(MEM_FLOW, "\t\tDct %d Msg Block Buffer: %x\n", Dct, PmuSramMsgBlockPtr);
    NBPtr->PsPtr->PmuSramMsgBlockPtr = PmuSramMsgBlockPtr;
    PmuSramMsgBlockPtr += 1;
  }

  return TRUE;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *    Free the PMU SRAM Message Block buffer.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 *     @return  TRUE - Free PMU SRAM Message buffer successfully.
 *     @return  FALSE - Fail to free PMU SRAM Message buffer.
 */

BOOLEAN
MemNPostPmuSramMsgBlockCZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  // De-allocate the PMU SRAM Message Block buffer.
  return (BOOLEAN) (HeapDeallocateBuffer (AMD_MEM_PMU_SRAM_MSG_BLOCK_HANDLE, &(NBPtr->MemPtr->StdHeader)) == AGESA_SUCCESS);
}

