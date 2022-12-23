/* $NoKeywords:$ */
/**
 * @file
 *
 * mnpmuD3cz.c
 *
 * Support functions for memory training using PMU for CZ
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project: AGESA
 * @e sub-project: (Mem/NB/CZ)
 * @e \$Revision: 317056 $ @e \$Date: 2015-04-20 22:06:48 +0800 (Mon, 20 Apr 2015) $
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
#include "mport.h"
#include "Library/IdsLib.h"
#include "Ids.h"
#include "cpuRegisters.h"
#include "mm.h"
#include "mn.h"
#include "mu.h"
#include "mt.h"
#include "mtsdi3.h"
#include "mnreg.h"
#include "mnpmu.h"
#include "mnPmuFirmwareCZ.h"
#include "mnPmuFirmwareD3cz.h"
#include "Filecode.h"
#include "Library/AmdHeapLib.h"
#include "mnPmuSramMsgBlockCZ.h"
#include "OptionMemory.h"
#include "mncz.h"
CODE_GROUP (G3_DXE)
RDATA_GROUP (G3_DXE)


#define FILECODE LIBRARY_MEM_NBCZLIB_MNPMUD3CZ_FILECODE



/*----------------------------------------------------------------------------
 *                          DEFINITIONS AND MACROS
 *
 *----------------------------------------------------------------------------
 */
#define PMU_TRAINS_ECC_LANES       0x80    ///< PMU trains ECC lanes
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


ROMDATA PMU_FIRMWARE PmuFirmwareD3ImageTableCZ[] = {
//
//  PMU Signature  Instance   Package String      NULL Reserved   Size                                           Image Data
//
  {{PMU_SIGNATURE,    '0',    PMU_PACKAGE_STRING,  0,     {0}  }, PMU_SRAM_DMEM_SIZE_CZ + PMU_SRAM_IMEM_SIZE_CZ, PMU_DDR3_CZ_9221   },
  {{PMU_SIGNATURE,    '1',    PMU_PACKAGE_STRING,  0,     {0}  }, PMU_IMAGE_NOT_USEABLE },
};
ROMDATA UINT8 PmuFirmwareD3ImageTableSizeCZ = GET_SIZE_OF (PmuFirmwareD3ImageTableCZ);

/*----------------------------------------------------------------------------
 *                            EXPORTED FUNCTIONS
 *
 *----------------------------------------------------------------------------
 */

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function sets the PMU sequence control for DRAM training
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */
// This is a placholder for D3 Specific Sequence Control
//
// VOID
// MemNSetPmuSequenceControlD3CZ (
//   IN OUT   MEM_NB_BLOCK *NBPtr
//   )
// {
//   LOCATE_HEAP_PTR LocHeap;
//   PMU_SRAM_MSG_BLOCK_CZ *PmuSramMsgBlockPtr;
//
//   LocHeap.BufferHandle = AMD_MEM_PMU_SRAM_MSG_BLOCK_HANDLE;
//
//   if (HeapLocateBuffer (&LocHeap, &(NBPtr->MemPtr->StdHeader)) != AGESA_SUCCESS) {
//     ASSERT(FALSE); // Could not locate heap for PMU SRAM Message Block buffer.
//   }
//
//   PmuSramMsgBlockPtr = (PMU_SRAM_MSG_BLOCK_CZ *) LocHeap.BufferPtr;
//   //
//   // Call Common Sequence Control
//   //
//   MemNSetPmuSequenceControlCZ(NBPtr);
// }
//

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function passes to PMU DRAM configuration over PMU SRAM for DDR3
 *     DRAM init and training
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNPopulatePmuSramConfigD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  PMU_SRAM_MSG_BLOCK_CZ *PmuSramMsgBlockPtr;
  //
  // Call Common Config routine
  //
  MemNPopulatePmuSramConfigCZ (NBPtr);
  //
  // DDR3 Unbuffered specific configuration
  //
  PmuSramMsgBlockPtr = (PMU_SRAM_MSG_BLOCK_CZ *) NBPtr->PsPtr->PmuSramMsgBlockPtr;
  //
  // NO DDR3 UNBUFFERED-SPECIFIC CONFIG
  //
  return;
}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function passes to PMU DRAM timings over PMU SRAM for DDR3 DRAM init and training.
 *     Timings are MemPstate dependent.
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNPopulatePmuSramTimingsD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  UINT32 Mr0;
  UINT32 Mr1;
  UINT32 Mr2;

  PMU_SRAM_MSG_BLOCK_CZ *PmuSramMsgBlockPtr;

  //
  // Call Common Timing routine
  //
  MemNPopulatePmuSramTimingsCZ (NBPtr);
  //
  // DDR4 Unbuffered-specific timings
  //
  PmuSramMsgBlockPtr = (PMU_SRAM_MSG_BLOCK_CZ *) NBPtr->PsPtr->PmuSramMsgBlockPtr;

  if (NBPtr->MemPstate == 0) {
    PmuSramMsgBlockPtr->M0CkeSetup = (UINT8) (NBPtr->ChannelPtr->DctAddrTmg & 0xFF);
    PmuSramMsgBlockPtr->M0CsOdtSetup = (UINT8) ((NBPtr->ChannelPtr->DctAddrTmg >> 8) & 0xFF);
    PmuSramMsgBlockPtr->M0AddrCmdSetup = (UINT8) (UINT8) ((NBPtr->ChannelPtr->DctAddrTmg >> 16) & 0xFF);
  } else {
    PmuSramMsgBlockPtr->Annex.D3u.M1CkeSetup = (UINT8) (NBPtr->ChannelPtr->DctAddrTmgPs1 & 0xFF);
    PmuSramMsgBlockPtr->Annex.D3u.M1CsOdtSetup = (UINT8) ((NBPtr->ChannelPtr->DctAddrTmgPs1 >> 8) & 0xFF);
    PmuSramMsgBlockPtr->Annex.D3u.M1AddrCmdSetup = (UINT8) ((NBPtr->ChannelPtr->DctAddrTmgPs1 >> 16) & 0xFF);
  }
  //
  // MR Commands
  //
  Mr0 = (UINT16) MemNGetBitFieldNb (NBPtr, BFMxMr0);
  Mr1 = (UINT16) MemNGetBitFieldNb (NBPtr, BFMxMr1);
  Mr2 = (UINT16) MemNGetBitFieldNb (NBPtr, BFMxMr2);

  // Program MrsAddress[8]=1 (DLL):DLL reset for PMU init.
  Mr0 |= 1 << 8;
  if (NBPtr->MemPstate == 0) {
    PmuSramMsgBlockPtr->Annex.D3u.M0_MR0 = (UINT16) Mr0;
    PmuSramMsgBlockPtr->Annex.D3u.M0_MR1 = (UINT16) Mr1;
    PmuSramMsgBlockPtr->Annex.D3u.M0_MR2 = (UINT16) Mr2;
  } else {
    PmuSramMsgBlockPtr->Annex.D3u.M1_MR0 = (UINT16) Mr0;
    PmuSramMsgBlockPtr->Annex.D3u.M1_MR1 = (UINT16) Mr1;
    PmuSramMsgBlockPtr->Annex.D3u.M1_MR2 = (UINT16) Mr2;
  }

  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tMR0: %04x\n", Mr0);
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tMR1: %04x\n", Mr1);
  IDS_HDT_CONSOLE (MEM_FLOW, "\t\t\tMR2: %04x\n", Mr2);

}

/* -----------------------------------------------------------------------------*/
/**
 *
 *     This function set the PMU sequence control for DRAM training
 *
 *     @param[in,out]   *NBPtr   - Pointer to the MEM_NB_BLOCK
 *
 */

VOID
MemNSetPmuSequenceControlD3CZ (
  IN OUT   MEM_NB_BLOCK *NBPtr
  )
{
  PMU_SRAM_MSG_BLOCK_CZ *PmuSramMsgBlockPtr;
  PmuSramMsgBlockPtr = (PMU_SRAM_MSG_BLOCK_CZ *) NBPtr->PsPtr->PmuSramMsgBlockPtr;
  //
  // Both images get program with same SequenceCtrl, each image would ignore the ones that did not apply to it.
  //
  if (NBPtr->RefPtr->PmuTrainMode == PMU_TRAIN_1D) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\tPMU 1D Training\n");
    // [0] 1=DevInit [1] 1=WrLvl Training, [2] 1=RxEnDly Training, [3] 1=1D Rd-Dqs Training, [4] 1=1D Wr-Dq Training.
    PmuSramMsgBlockPtr->SequenceCtrl = 0x1F;
  } else if (NBPtr->RefPtr->PmuTrainMode == PMU_TRAIN_1D_2D_READ) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\tPMU 1D and 2D read Training\n");
    // [0] 1=DevInit [1] 1=WrLvl Training, [2] 1=RxEnDly Training, [3] 1=1D Rd-Dqs Training, [4] 1=1D Wr-Dq Training, [5] 1=2D Read Training.
    PmuSramMsgBlockPtr->SequenceCtrl = 0x3F;
  } else if (NBPtr->RefPtr->PmuTrainMode == PMU_TRAIN_1D_2D) {
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\tPMU 1D and 2D Training\n");
    // [0] 1=DevInit [1] 1=WrLvl Training, [2] 1=RxEnDly Training, [3] 1=1D Rd-Dqs Training, [4] 1=1D Wr-Dq Training, [5] 1=2D Read Training, [6] 1=2D Write Training.
    PmuSramMsgBlockPtr->SequenceCtrl = 0x7F;
  } else {
    IDS_HDT_CONSOLE (MEM_FLOW, "\t\tPMU Train auto\n");
    //
    // PMU 1D Training
    //
    PmuSramMsgBlockPtr->SequenceCtrl = 0x1F;
  }
}
